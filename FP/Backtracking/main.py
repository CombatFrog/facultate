from Presentation.console import Consola
from Backtracking.backtracking import BacktrackingIter, BacktrackingRec

backIter = BacktrackingIter()
backRec = BacktrackingRec()
consola = Consola(backIter, backRec)
consola.run()