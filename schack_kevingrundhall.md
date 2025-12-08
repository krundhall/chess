Min plan är att göra ett schackspel med ett SFML gränssnitt. Tanken är att man lokalt skall kunna spela ett parti schack lokalt på en dator från start till slut med alla specialregler fullt fungerande. Partiet skall sparas till en daterad fil med FEN notering så att man i vilken schackapp som helst kan spela tillbaks partiet.
Tanken är i framtiden att expandera projektet när jag har utvecklats mer som programmerare. Jag hade velat testa mig på att implementera online multiplayer. Men det är lite utanför denna kursens scope. Att även kunna implementera någon form av schackdatabas-hjälp för att kunna lista ut användares bästa möjliga drag hade varit coolt, men får se vart nivån ligger. 


För mitt klassdiagram så har jag ritat upp det som jag är rätt säker kommer behöva vara med i mitt schackprogram.

Först och främst så har vi den abstrakta klassen "Piece" som kommer vara basklass för alla dem olika pjästyperna. Piece kommer att erhålla för pjäsernas färg, typ men även position. Positionen hade jag tänkt att hantera genom en separat struct för att lagra x och y koordinater. Naturligtvis kommer Piece även ha get funktioner för att kunna fråga vad en specifik pjäs har för färg, position eller typ. 

Jag är lite osäker på hur jag skall hantera drag, men såhär tänker jag nu:
Piece objekt har alla sina möjliga drag i en vector och den bryr sig inte om dem är lagliga eller ej. När ett drag väl görs så kommer en annan klass kolla om det draget som användaren ha gjort är möjligt från första börja, sedan kommer den validera draget med respekt till hur brädet ser ut.

Board ansvarar för hur bordet (givetvis). Den kommer hålla en 8*8 statisk array som representerar schackbrädet, och på så vis får jag ett smidigt x och y koordinat system.
Klassen Board kommer även ha en set/get för att hämta information vad som finns på en given ruta. Utöver det så tänker jag en enkel init funktion som används som ett slags default läge. Init ställer pjäserna där dem skall vara inför ett nytt parti kortfattat.

Game klassen är själva spelloopen. Klassen som egentligen håller i spakarna och dikteras vad som skall göras på brädet. I nuläget tror jag att Game kommer att validera alla drag och säga till Board att uppdateras, men om det blir för rörigt så är jag förberedd på att bryta ner game och faktorisera ut en slags "RulesEngine" av något slag som sköter validering av drag själv. Game kommer även erhålla en historik metod, som skriver parties draghistorik till fil. Detta kommer använda "FEN" systemet som internationellt används för att representera schackpartin. 

Renderer klassen var tänkt som något slags interface för att hantera SFML renderingen. På såsätt håller jag all SFML logik utanför min schacklogik, och borde få en renare kod. 