
Piece

Abstrakt basklass för alla pjäser. erhåller gemensamma attributer så som färg och position
Definerar virtuella metoder för att beräkna drag
Polymorfi för subklasser


King/Queen/Rook/Bishop/Knight/Pawn

Implementation av respektive pjäs
Erhåller logik för pjäsens tillåtna drag
Hanterar specialfall för sin typ (te.x bondens en passant)


Position

Struktor för att representera en ruta på brädet (rad/kolumn)
Borde (hoppas jag) underlätta att skicka runt koordinater


Board

Håller 8x8 brädet med pjäser.
Exekverar drag, validerar drag
Hanterar kontroll av schack/schackmatt


Game

Övergripande spelloop
Turordning, historik, spelslut
Filhantering
Spelstatus
Erhåller draghistorik


Renderer (SFML)

Ansvarar som ett interface med SFML
Ritar brädet och pjäser
Laddar sprites
Uppdaterar grafik baserat på Game-tillståendet


InputHandler (SFML)

Tar emot input och översätter den till schackdrag
Hanterar val av pjäs
Kommunicerar draget till Game



Steg 0:
    Användare klickar på ruta
    Renderer/UI skickar:
        en vald position (ex (6,4) -> vit bonde på e2)
        till game/board

Steg 1:
    Om p == nullptr -> inget händer
    Om det inte är rätt färgs tur -> blockera (Game)

Steg 2:
    Game frågar pjäsen om dess pseudo-legal moves
        Detta returnerar bara rörelser enligt pjäsens logik
            Bishop -> diagonaler
            Rook -> raka linker
            osv
        Det returnerar INTE
            Schackkontroll
            Pin
            en passant
            osv

Steg 3:
    Game filtrerar bort illegala drag
    Game simulerar draget på ett kopierat Board
    (eller genom att göra draget, köra checks, ångra om det behövs)
    Game testar:
        Står min kung i schack efter draget (Pin check)
        Är detta ett specialdrag?
        Är rockad giltigt?
        Är en passant giltigt?
        Är promotion nödvändigt?

Steg 4:
    Game berättar de drag UI behöver visa
    Renderer färgar rutor, highlightar osv
    UI pratar aldrig med pjäsen direkt, utan bara med Game

Steg 5:
    Använder väljer ett giltigt drag
    UI klick -> Game får:
        Start position
        Slut position
    Game kontrollerar att start->slut finns i legal moves

Steg 6:
    Game exekverar draget på Board
    Game loggar draget i historiken
    Game byter tur

Steg 7:
    Renderer använder Board för att rita om brädet