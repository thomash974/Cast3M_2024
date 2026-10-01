#!/usr/bin/env python3
"""Colorisation de fichiers sources a partir de definitions de syntaxe Kate/KWrite (XML).

Le script relit les fichiers de syntaxe utilises par Kate (gibiane.xml, esope.xml, ...)
et applique leurs listes de mots-cles, leurs contextes et leurs regles. Il produit
une page HTML autonome (clair / sombre, numeros de ligne, bouton de copie).

Exemples :
    python3 colorise_kate.py -s gibiane.xml esope.xml -o apercu.html cas_test.dgibi routine.eso
    python3 colorise_kate.py -s gibiane.xml -o apercu.html mazars.dgibi

La syntaxe est choisie d'apres l'extension du fichier source (attribut "extensions"
du fichier XML : *.dgibi;*.procedur pour Gibiane, *.eso pour Esope).

Regles Kate prises en charge : keyword, RegExpr, DetectChar, Detect2Chars,
StringDetect, AnyChar, Float, Int, DetectSpaces, IncludeRules, ainsi que
lineEndContext, fallthrough, column et firstNonSpace.
Ecart volontaire : les flottants a exposant Fortran (1.D-6) sont reconnus.

Verification des noms (Gibiane) : les variables definies par une affectation (NOM = ...)
sont controlees. Une variable est signalee (stderr + bandeau dans la page + ligne surlignee)
si elle est coloree comme mot-cle / operateur, ou si elle porte le meme nom qu'un mot
entre quotes utilise dans le fichier ('KTR0' ... KTR0 = 1.D-4). Desactivable avec
--sans-verification.
"""
import argparse
import colorsys
import fnmatch
import html
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

# Delimiteurs de mots par defaut de Kate
DELIMITEURS = set(' \t!%&()*+,-./:;<=>?[\\]^{|}~')

# Styles par defaut de Kate (theme clair) : (couleur, gras, italique)
STYLES_DEFAUT = {
    'dsNormal': (None, False, False),
    'dsKeyword': ('#1f1c1b', True, False),
    'dsDataType': ('#0057ae', False, False),
    'dsDecVal': ('#b08000', False, False),
    'dsBaseN': ('#b08000', False, False),
    'dsFloat': ('#b08000', False, False),
    'dsChar': ('#924c9d', False, False),
    'dsString': ('#bf0303', False, False),
    'dsComment': ('#898887', False, True),
    'dsOthers': ('#006e28', False, False),
    'dsAlert': ('#bf0303', True, False),
    'dsFunction': ('#644a9b', False, False),
    'dsRegionMarker': ('#0057ae', False, False),
    'dsError': ('#bf0303', False, False),
}

VRAI = ('true', 'TRUE', 'True', '1')


class Syntaxe:
    """Definition de syntaxe Kate chargee depuis un fichier XML."""

    def __init__(self, chemin):
        brut = Path(chemin).read_bytes().replace(b'\r', b'')
        brut = re.sub(rb'<!DOCTYPE[^>]*>', b'', brut)
        racine = ET.fromstring(brut)
        self.nom = racine.get('name', Path(chemin).stem)
        self.extensions = [e.strip().lower() for e in racine.get('extensions', '').split(';') if e.strip()]

        gen = racine.find('general/keywords')
        self.insensible = gen is not None and gen.get('casesensitive') in ('0', 'false', 'FALSE')

        self.listes = {}
        for liste in racine.iter('list'):
            mots = {(i.text or '').strip() for i in liste.findall('item')}
            self.listes[liste.get('name')] = {m.lower() if self.insensible else m for m in mots if m}

        self.contextes = {}
        self.premier = None
        for ctx in racine.find('highlighting/contexts').findall('context'):
            nom = ctx.get('name')
            if self.premier is None:
                self.premier = nom
            self.contextes[nom] = {
                'attribut': ctx.get('attribute'),
                'fin_ligne': ctx.get('lineEndContext', '#stay'),
                'fallthrough': ctx.get('fallthrough') in VRAI,
                'fallthrough_ctx': ctx.get('fallthroughContext', '#stay'),
                'regles': list(ctx),
            }

        self.styles = {}
        for it in racine.iter('itemData'):
            self.styles[it.get('name')] = {
                'defaut': (it.get('defStyleNum') or 'dsNormal').strip(),
                'couleur': it.get('color'),
                'gras': it.get('bold'),
                'italique': it.get('italic'),
            }

        self._cache_regles = {}
        self._cache_regex = {}

    # ------------------------------------------------------------------ regles
    def _regles(self, nom, vus=None):
        """Liste aplatie des regles d'un contexte (IncludeRules developpes)."""
        if nom in self._cache_regles:
            return self._cache_regles[nom]
        vus = (vus or set()) | {nom}
        resultat = []
        for regle in self.contextes[nom]['regles']:
            if regle.tag == 'IncludeRules':
                cible = regle.get('context', '')
                if cible in self.contextes and cible not in vus:
                    resultat.extend(self._regles(cible, vus))
            else:
                resultat.append((nom, regle))
        self._cache_regles[nom] = resultat
        return resultat

    def _regex(self, motif, insensible):
        cle = (motif, insensible)
        if cle not in self._cache_regex:
            self._cache_regex[cle] = re.compile(motif, re.IGNORECASE if insensible else 0)
        return self._cache_regex[cle]

    def _longueur(self, regle, ligne, pos):
        """Longueur reconnue par la regle en position pos, ou None."""
        t = regle.tag
        col = regle.get('column')
        if col is not None and int(col) != pos:
            return None
        if regle.get('firstNonSpace') in VRAI and ligne[:pos].strip():
            return None
        if t == 'keyword':
            if pos > 0 and ligne[pos - 1] not in DELIMITEURS:
                return None
            fin = pos
            while fin < len(ligne) and ligne[fin] not in DELIMITEURS:
                fin += 1
            mot = ligne[pos:fin]
            mot = mot.lower() if self.insensible else mot
            return fin - pos if mot and mot in self.listes.get(regle.get('String'), ()) else None
        if t == 'RegExpr':
            m = self._regex(regle.get('String'), regle.get('insensitive') in VRAI).match(ligne, pos)
            return m.end() - pos if m and m.end() > pos else None
        if t == 'DetectChar':
            c = regle.get('char', '')
            return 1 if len(c) == 1 and ligne.startswith(c, pos) else None
        if t == 'Detect2Chars':
            c = (regle.get('char') or '') + (regle.get('char1') or '')
            return 2 if len(c) == 2 and ligne.startswith(c, pos) else None
        if t == 'StringDetect':
            s = regle.get('String', '')
            cible = ligne[pos:pos + len(s)]
            egal = cible.lower() == s.lower() if regle.get('insensitive') in VRAI else cible == s
            return len(s) if s and egal else None
        if t == 'AnyChar':
            return 1 if pos < len(ligne) and ligne[pos] in regle.get('String', '') else None
        if t == 'Float':
            m = self._regex(r'(?<![\w])(\d+\.\d*|\.\d+)([eEdD][+-]?\d+)?|(?<![\w])\d+[eEdD][+-]?\d+', False).match(ligne, pos)
            return m.end() - pos if m else None
        if t == 'Int':
            m = self._regex(r'(?<![\w])\d+', False).match(ligne, pos)
            return m.end() - pos if m else None
        if t == 'DetectSpaces':
            m = self._regex(r'[ \t]+', False).match(ligne, pos)
            return m.end() - pos if m else None
        return None

    @staticmethod
    def _changer(pile, spec):
        spec = spec or '#stay'
        if spec == '#stay':
            return
        while spec.startswith('#pop'):
            if len(pile) > 1:
                pile.pop()
            spec = spec[4:]
        spec = spec.lstrip('!')
        if spec and spec != '#stay':
            pile.append(spec)

    # ---------------------------------------------------------------- coloration
    def colorier(self, texte):
        """Retourne, pour chaque ligne, une liste de segments (attribut, texte)."""
        pile = [self.premier]
        resultat = []
        for ligne in texte.replace('\r', '').split('\n'):
            segments = []
            pos = 0
            garde = 0
            while pos < len(ligne):
                ctx = self.contextes[pile[-1]]
                trouve = None
                for nom_ctx, regle in self._regles(pile[-1]):
                    n = self._longueur(regle, ligne, pos)
                    if n:
                        trouve = (n, regle.get('attribute') or self.contextes[nom_ctx]['attribut'], regle.get('context'))
                        break
                if trouve:
                    n, attribut, suite = trouve
                    ajouter(segments, attribut, ligne[pos:pos + n])
                    pos += n
                    self._changer(pile, suite)
                    garde = 0
                elif ctx['fallthrough'] and garde < 20:
                    self._changer(pile, ctx['fallthrough_ctx'])
                    garde += 1
                else:
                    ajouter(segments, ctx['attribut'], ligne[pos])
                    pos += 1
                    garde = 0
            self._changer(pile, self.contextes[pile[-1]]['fin_ligne'])
            resultat.append(segments)
        return resultat

    def style(self, attribut):
        """(couleur claire, gras, italique) pour un attribut."""
        st = self.styles.get(attribut, {'defaut': 'dsNormal', 'couleur': None, 'gras': None, 'italique': None})
        couleur, gras, ital = STYLES_DEFAUT.get(st['defaut'], STYLES_DEFAUT['dsNormal'])
        if st['couleur']:
            couleur = st['couleur']
        if st['gras'] is not None:
            gras = st['gras'] in VRAI
        if st['italique'] is not None:
            ital = st['italique'] in VRAI
        return couleur, gras, ital, st['defaut']


def ajouter(segments, attribut, texte):
    if segments and segments[-1][0] == attribut:
        segments[-1] = (attribut, segments[-1][1] + texte)
    else:
        segments.append((attribut, texte))


def classe(attribut):
    return 'k-' + re.sub(r'\W+', '-', (attribut or 'normal').lower()).strip('-')


def eclaircir(couleur):
    """Version claire d'une couleur, lisible sur fond sombre."""
    couleur = couleur.lstrip('#')
    r, g, b = (int(couleur[i:i + 2], 16) / 255 for i in (0, 2, 4))
    h, l, s = colorsys.rgb_to_hls(r, g, b)
    l = max(l, 0.72)
    s = min(s, 0.75)
    r, g, b = colorsys.hls_to_rgb(h, l, s)
    return '#%02x%02x%02x' % (round(r * 255), round(g * 255), round(b * 255))


def verifier_noms(lignes_segments, lignes_texte):
    """Detecte les variables homonymes d'un mot-cle ou d'un operateur.

    Retourne une liste (numero de ligne, nom, raison).
    """
    mots_quotes = set()
    for segments in lignes_segments:
        for attribut, texte in segments:
            if attribut.lower() == 'string':
                m = re.fullmatch(r"'(\w+)'", texte)
                if m:
                    mots_quotes.add(m.group(1).upper())
    motif = re.compile(r"(?:^|;)\s*((?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*)\s*=(?!=)")
    avertissements = []
    for numero, (segments, texte) in enumerate(zip(lignes_segments, lignes_texte), 1):
        if not segments or segments[0][0].lower() == 'comment':
            continue
        attribut_par_car = []
        for attribut, morceau in segments:
            attribut_par_car.extend([attribut] * len(morceau))
        for m in motif.finditer(texte):
            for nom in re.finditer(r"[A-Za-z_]\w*", m.group(1)):
                pos = m.start(1) + nom.start()
                attribut = attribut_par_car[pos] if pos < len(attribut_par_car) else 'Normal Text'
                mot = nom.group(0)
                if attribut.lower() != 'normal text':
                    raison = "colore comme \u00ab %s \u00bb (mot-cle ou operateur)" % attribut
                elif mot.upper() in mots_quotes:
                    raison = "meme nom que le mot-cle '%s' utilise entre quotes" % mot.upper()
                else:
                    continue
                avertissements.append((numero, mot, raison))
    return avertissements


# ------------------------------------------------------------------------ HTML
MODELE = """<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<title>__TITRE__</title>
<style>
:root {
    box-sizing: border-box;
    padding-top: env(safe-area-inset-top, 0px);
    padding-bottom: env(safe-area-inset-bottom, 0px);
    --bg: #ffffff; --panel: #f6f7f9; --fg: #1f1c1b; --muted: #8a8f98; --border: #dcdfe4;
    --accent: #2a5bd7;
__VARS_CLAIR__
}
@media (prefers-color-scheme: dark) {
    :root:not([data-theme="light"]) {
        --bg: #14161a; --panel: #1c1f25; --fg: #e6e6e6; --muted: #7b818c; --border: #2b3038;
        --accent: #7ea2ff;
__VARS_SOMBRE__
    }
}
:root[data-theme="dark"] {
    --bg: #14161a; --panel: #1c1f25; --fg: #e6e6e6; --muted: #7b818c; --border: #2b3038;
    --accent: #7ea2ff;
__VARS_SOMBRE__
}
html { scroll-padding-top: env(safe-area-inset-top, 0px); }
*, *::before, *::after { box-sizing: border-box; }
body {
    margin: 0; background: var(--bg); color: var(--fg);
    font: 15px/1.5 system-ui, -apple-system, "Segoe UI", Roboto, sans-serif;
}
main { max-width: 1100px; margin: 0 auto; padding: 20px 16px 40px; }
h1 { font-size: 1.15rem; margin: 0 0 4px; }
.sub { color: var(--muted); font-size: .85rem; margin-bottom: 14px; }
.onglets { display: flex; gap: 6px; flex-wrap: wrap; margin-bottom: 10px; }
.onglets button, .copier {
    font: inherit; font-size: .85rem; cursor: pointer; color: var(--fg);
    background: var(--panel); border: 1px solid var(--border); border-radius: 6px; padding: 5px 12px;
}
.onglets button[aria-selected="true"] { border-color: var(--accent); color: var(--accent); }
.entete { display: flex; justify-content: space-between; align-items: center; gap: 10px; margin: 6px 0; flex-wrap: wrap; }
.legende { display: flex; gap: 6px 14px; flex-wrap: wrap; font-size: .8rem; }
.legende span { font-family: ui-monospace, "SF Mono", Menlo, Consolas, "DejaVu Sans Mono", monospace; }
.code {
    background: var(--panel); border: 1px solid var(--border); border-radius: 8px;
    overflow-x: auto; max-width: 100%; padding: 10px 0; counter-reset: ligne;
    font: 13px/1.55 ui-monospace, "SF Mono", Menlo, Consolas, "DejaVu Sans Mono", monospace;
    white-space: pre; tab-size: 4;
}
.ln { display: block; counter-increment: ligne; padding-right: 16px; min-width: max-content; }
.ln::before {
    content: counter(ligne); display: inline-block; width: 4ch; margin-right: 1.4ch; padding-right: 1ch;
    text-align: right; color: var(--muted); border-right: 1px solid var(--border); user-select: none;
}
section[hidden] { display: none; }
.alerte {
    border: 1px solid #bf0303; background: rgba(191, 3, 3, .12); border-radius: 8px;
    padding: 8px 14px; margin: 6px 0 10px; font-size: .85rem;
}
.alerte ul { margin: 4px 0 0; padding-left: 20px; }
.alerte code { font-family: ui-monospace, "SF Mono", Menlo, Consolas, "DejaVu Sans Mono", monospace; }
.ln-alerte { background: rgba(191, 3, 3, .16); }
__CSS_CLASSES__
</style>
</head>
<body>
<main>
    <h1>__TITRE__</h1>
    <div class="sub">Coloration d'apres les fichiers de syntaxe Kate : __SYNTAXES__</div>
    <div class="onglets" role="tablist">__ONGLETS__</div>
__SECTIONS__
</main>
<script>
(function () {
    var boutons = document.querySelectorAll('.onglets button');
    var sections = document.querySelectorAll('section[data-nom]');
    function afficher(i) {
        for (var k = 0; k < sections.length; k++) {
            sections[k].hidden = (k !== i);
            if (boutons[k]) boutons[k].setAttribute('aria-selected', k === i ? 'true' : 'false');
        }
    }
    for (var i = 0; i < boutons.length; i++) {
        (function (n) { boutons[n].addEventListener('click', function () { afficher(n); }); })(i);
    }
    if (sections.length) afficher(0);
    var cop = document.querySelectorAll('.copier');
    for (var j = 0; j < cop.length; j++) {
        cop[j].addEventListener('click', function (ev) {
            var bouton = ev.currentTarget;
            var lignes = bouton.closest('section').querySelectorAll('.ln');
            var texte = Array.prototype.map.call(lignes, function (l) { return l.textContent; }).join('\\n') + '\\n';
            var ok = function () { bouton.textContent = 'Copie'; setTimeout(function () { bouton.textContent = 'Copier le code'; }, 1500); };
            var secours = function () {
                try {
                    var ta = document.createElement('textarea');
                    ta.value = texte; document.body.appendChild(ta); ta.select();
                    document.execCommand('copy'); document.body.removeChild(ta); ok();
                } catch (e) { bouton.textContent = 'Copie impossible'; }
            };
            try {
                if (navigator.clipboard && navigator.clipboard.writeText) {
                    navigator.clipboard.writeText(texte).then(ok, secours);
                } else { secours(); }
            } catch (e) { secours(); }
        });
    }
})();
</script>
</body>
</html>
"""


def choisir_syntaxe(syntaxes, fichier):
    nom = Path(fichier).name.lower()
    for s in syntaxes:
        if any(fnmatch.fnmatch(nom, motif) for motif in s.extensions):
            return s
    raise SystemExit("Aucune syntaxe ne correspond a l'extension de %s" % fichier)


def construire_page(sources, syntaxes, titre, verifier=True):
    styles_utilises = {}   # classe -> (couleur, gras, italique, defaut)
    onglets, sections, noms_syntaxes, tous_avertissements = [], [], [], []
    for i, chemin in enumerate(sources):
        syn = choisir_syntaxe(syntaxes, chemin)
        if syn.nom not in noms_syntaxes:
            noms_syntaxes.append(syn.nom)
        texte_source = Path(chemin).read_text(encoding='utf-8', errors='replace')
        lignes = syn.colorier(texte_source)
        lignes_texte = texte_source.replace('\r', '').split('\n')
        if lignes and lignes[-1] == []:
            lignes.pop()          # ligne vide finale due au retour a la ligne terminal
            lignes_texte.pop()
        avertissements = []
        if verifier and syn.nom.lower() == 'gibiane':
            avertissements = verifier_noms(lignes, lignes_texte)
        lignes_alerte = {a[0] for a in avertissements}
        tous_avertissements.extend((Path(chemin).name,) + a for a in avertissements)
        utilises = {}
        corps = []
        for numero, segments in enumerate(lignes, 1):
            morceaux = []
            for attribut, texte in segments:
                couleur, gras, ital, defaut = syn.style(attribut)
                echappe = html.escape(texte, quote=False)
                if defaut == 'dsNormal' and not couleur and not gras and not ital:
                    morceaux.append(echappe)
                    continue
                cls = classe(attribut)
                styles_utilises[cls] = (couleur, gras, ital, defaut)
                utilises[cls] = attribut
                morceaux.append('<span class="%s">%s</span>' % (cls, echappe))
            cls_ligne = 'ln ln-alerte' if numero in lignes_alerte else 'ln'
            corps.append('<span class="%s">%s</span>' % (cls_ligne, ''.join(morceaux)))
        legende = ''.join('<span class="%s">%s</span>' % (c, html.escape(a)) for c, a in utilises.items())
        nom = Path(chemin).name
        onglets.append('<button type="button" role="tab" aria-selected="false">%s</button>' % html.escape(nom))
        bandeau = ''
        if avertissements:
            items = ''.join(
                '<li>ligne %d : <code>%s</code> \u2014 %s</li>' % (n, html.escape(mot), html.escape(raison))
                for n, mot, raison in avertissements)
            bandeau = ('    <div class="alerte"><strong>Collision de noms possible</strong>'
                       '<ul>%s</ul></div>\n' % items)
        sections.append(
            '<section data-nom="%s">\n%s'
            '    <div class="entete"><div class="legende">%s</div>'
            '<button type="button" class="copier">Copier le code</button></div>\n'
            '    <div class="code">%s</div>\n</section>' % (html.escape(nom), bandeau, legende, ''.join(corps)))

    clair, sombre, css = [], [], []
    for cls, (couleur, gras, ital, defaut) in styles_utilises.items():
        base = couleur or '#1f1c1b'
        clair.append('    --%s: %s;' % (cls, base))
        sombre.append('        --%s: %s;' % (cls, eclaircir(base)))
        regle = 'color: var(--%s);' % cls
        if gras:
            regle += ' font-weight: 700;'
        if ital:
            regle += ' font-style: italic;'
        if defaut == 'dsAlert':
            regle += ' background: rgba(191, 3, 3, .15);'
        css.append('.%s { %s }' % (cls, regle))

    page = MODELE
    remplacements = {
        '__TITRE__': html.escape(titre),
        '__SYNTAXES__': html.escape(', '.join(noms_syntaxes)),
        '__VARS_CLAIR__': '\n'.join(clair),
        '__VARS_SOMBRE__': '\n'.join(sombre),
        '__CSS_CLASSES__': '\n'.join(css),
        '__ONGLETS__': ''.join(onglets),
        '__SECTIONS__': '\n'.join(sections),
    }
    for cle, valeur in remplacements.items():
        page = page.replace(cle, valeur)
    return page, tous_avertissements


def main():
    ap = argparse.ArgumentParser(description="Colorise des sources avec des syntaxes Kate (XML).")
    ap.add_argument('sources', nargs='+', help='fichiers sources (.dgibi, .procedur, .eso ...)')
    ap.add_argument('-s', '--syntaxes', nargs='+', required=True, help='fichiers de syntaxe XML')
    ap.add_argument('-o', '--sortie', default='apercu.html')
    ap.add_argument('-t', '--titre', default=None)
    ap.add_argument('--sans-verification', action='store_true',
                    help='desactive le controle des noms de variables (Gibiane)')
    args = ap.parse_args()
    syntaxes = [Syntaxe(x) for x in args.syntaxes]
    titre = args.titre or (Path(args.sources[0]).name if len(args.sources) == 1 else 'Apercu des sources')
    page, avertissements = construire_page(args.sources, syntaxes, titre, not args.sans_verification)
    Path(args.sortie).write_text(page, encoding='utf-8')
    print('Ecrit :', args.sortie)
    for fichier, numero, mot, raison in avertissements:
        print('ATTENTION %s ligne %d : variable %s %s' % (fichier, numero, mot, raison), file=sys.stderr)
    if not avertissements:
        print('Verification des noms : aucune collision detectee')


if __name__ == '__main__':
    sys.exit(main())
