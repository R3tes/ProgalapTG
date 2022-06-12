# Kötelező program: Sakk

A program az SZTE TTIK Tehetséggondozás: Programozás alapjai kurzus keretein belül készült. 

Forrásként felhasználtuk a [Zöld sakk](https://zoldsakk.hu/rules.php) oldal által leírt szabályokat, illetve próbáltunk eleget tenni a kiírt specifikációknak.

A bábukat a lower- és uppercase különbözteti meg, a fekete játékos bábui kisbetűvel vannak jelölve, a fehéré pedig nagybetűkkel.

Bábuk jelölései a táblán
* **[B] [b] Bástya**
* **[F] [f] Futó**
* **[H] [h] Huszár**
* **[V] [v] Vezér**
* **[K] [k] Király**
* **[G] [g] Gyalog**

Néhány helyen eltértünk az eredeti szabályoktól, esetleg azokat egészítettük ki/interpretáltuk. Tekintettel arra, hogy a lépések helyességének ellenőrzése
nem volt követelmény, sajátos lépések is kialakulhattak. A gyalog a kezdőpozíciójából is egyet léphet, ütni pedig a szabályoknak megfelelően
jobbra és balra tud. Egy körben egy fajta lépés végezhető, például sáncolunk, átváltozunk vagy simán lépünk/ütünk.

Átváltozás a zöld sakk oldalon leírtakkal azonos, azaz akármilyen tisztté (vezérré, bástyává, futóvá vagy huszárrá) változhatunk át.

A győzelmet az jelenti, ha valamelyik játékos leüti a másik játékos királyát és vezérét. Ilyesmi nem volt a követelmények között, viszont úgy gondoltuk, hogy
valamilyen formában nyerni is lehessen.

Tekinthetünk erre a játékra úgy is, mint sakk szárnyakkal, hiszen a lépések/ütés helyessége alapvetően ellenőrizve van, viszont a bábuk átléphetnek más babuk fölött is.

A programban a sáncolás lépését is kissé átgondoltuk. A Zöld sakkban látott szabályoktól eltérően a királynak egyet kell lépnie valamely bástyája felé,
viszont a bástya és király közötti hely úgyanúgy üres kell hogy legyen, valamint mindkét fajta bábu a tábla felállításakori kezdő pozícióban kell, hogy álljon.
Ezeken felül viszont a sáncolás művelete ugyanúgy történik.

A buildeléshez a make rendszer van használva, három targettel: all, clean, test. Készült néhány kifejezetten primitív bash által értelmezhető script is, ezek gyakorlatilag
csak meghívják a make parancsokat, illetve a run a végén tisztít is.

A CUnit tesztek főprogramja a utest, a megvalósítás pedig az eredetihez hasonlóan kiszervezve lett elvégezve (utest-sakk header és megvalósítás).
A főprogram maga a main mappában, a függvények megvalósítása és deklarálása pedig a libsakk mappában találhatók.

A tesztek csak linux rendszer alatt fognak lefutni, mivel a standard input és outputok átírányítása ebben az esetben linux-specifikus.

A program, tesztek és dinamikus viselkedés Windows Subsystem for Linux 2 segítségével lettek elvégezve, más operációs rendszeren nem működnek garantáltan.

Szükség esetén a forráskód elérhető [Githubon](https://github.com/R3tes/ProgalapTG) is, viszont ezért nem vállalunk felelősséget.

A forráskódban a nem közös részeken kívül egysoros kommentekkel jelölve lettek az adott részek készítői.
Pl.:
//Név
valami függvény(){}

A programot készítette:
* **Bakk Ábel**
* **Búcsú Áron**