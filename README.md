# NHZ_Prog_1

## Immortal Combat

**Kezdéskor több karakter közül lehet választani:**
 - Wizard
 - Archer
 - Assassin
 - Warrior
 - Tank
 - Priest

ellenségeket kell legyőzni **Exp**-ért
a játék célja hogy minél **messzebb** juss mielött meghalnál

*6 karakter * 3 képesség*
*több ellenségfajta*

## Journey of The Wizard

**Régi python projektem újraélesztése és továbbfejlesztése NHZ keretein belül**

### Concept
 - Csak a Wizard marad meg és róla fog szólni a játék
 - Mindennek a neve **"smth of smth"** lesz mint a játék neve is
 - a játék menete abból áll hogy le kell győzni 4 ellenséget aztán egy **Boss**-t
 - az ellenségek **Exp**-t adnak amivel szintet lép karakterünk és egy tárgyat kap
 - ezek a tárgyak segítségével lehet erősödni
 - kezdéskor kiválasztott nehézségi szinten kívül Boss-onként is erősödnek az ellenségek
 - illetbe Boss-onként változik a **téma/stage** is forest, cave és evil castle sorba jönnek
 - a 3. stage után opcio az endless mode ahol már random követik egymast a témák

### Technikai notes
 - fő library ncurses
 - ASCII art
 - menu navigation nyilakkal
 - save / load game state
 - különféle menuk menu
 - statok:
    - max hp/mana
    - armor
    - crit chance
    - miss chance
    - hp/mana regeneration
    - ability strebgth
 - több item
 - több enemy
 - több boss