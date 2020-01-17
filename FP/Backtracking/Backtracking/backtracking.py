class BacktrackingIter():

  def consistent(self, x):
    return not x[len(x) - 1] in x[:len(x) - 1] and list(x) == list(sorted(x))

  def solutionFound(self, lista, x):
    sol = "["
    for i in x[:-1]:
      sol += str(lista[i]) + ", "
    sol += str(lista[x[-1]]) + "]"
    print(sol)

  def solution(self, lista, x, n):
    suma = 0
    for i in x:
      suma += lista[i]
    return suma % n == 0

  def backIter(self, n, lista):
    x = [-1]
    while len(x) > 0:
      choose = False
      while not choose and x[-1] < len(lista) - 1:
        x[-1] += 1
        choose = self.consistent(x)
      if choose:
        if self.solution(lista, x, n):
          self.solutionFound(lista, x)
        x.append(-1)
      else:
        x = x[:-1]

class BacktrackingRec():

  def consistent(self, x):
    return not x[-1] in x[:-1] and list(x) == list(sorted(x))

  def solutionFound(self, x):
    sol = "["
    for i in x[:-1]:
      sol += str(i) + ", "
    sol += str(x[-1]) + "]"
    print(sol)

  def solution(self, x, n):
    return sum(x) % n == 0

  def nextElem(self, lista, i):
    if i < len(lista):
      return lista[i]
    return None

  def backRec(self, n, lista, x):
    el = lista[0]
    x.append(el)
    i = 0
    while el is not None:
      i += 1
      x[-1] = el
      if self.consistent(x):
        if self.solution(x, n):
          self.solutionFound(x)
        self.backRec(n, lista, x[:])
      el = self.nextElem(lista, i)





