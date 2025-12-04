
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


Move
Representerar ett drag
Innehåller start och slut position, flyttad pjäs, slagen pjäs och specialdrag
Kommer användas av Board för validering av drag och av Game för historik


Board

Håller 8x8 brädet med pjäser.
Exekverar drag, validerar drag
Hanterar kontroll av schack/schackmatt


Game
Övergripande spelloop
Turordning, historik, spelslut
Filhantering
Spelstatus


MoveHistory

Erhåller historiken på ett parti
Kan användas för att verifiera rockadregler, eller sparande av spel. 


Renderer (SFML)

Ansvarar som ett interface med SFML
Ritar brädet och pjäser
Laddar sprites
Uppdaterar grafik baserat på Game-tillståendet


InputHandler (SFML)

Tar emot input och översätter den till schackdrag
Hanterar val av pjäs
Kommunicerar draget till Game