def nv(n):
  for j in range(n,-1,-1):
    if dist[j] < dist[n]-limit:
      return j

def bb (n):
  if arr[n] != None:
    return arr[n]
  if n<0:
    return 0
  if n == None:
    return 0
  if n == 0:
    return rev[0]
  if dist[n-1 ]< dist[n] - limit:
    result = rev[n] + bb(n-1)
  else:
    j = nv(n)
    if j == None:
      j = -1
    result = max((rev[n] + bb(j)) , bb(n-1))
  arr[n] = result
  return result

dist = [50, 80, 90, 150]
rev = [75, 25, 65, 45]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [10, 20, 30, 40]
rev  = [100, 200, 300, 400]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))


dist = [10, 20, 30, 40]
rev  = [400, 300, 200, 100]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))


dist = [10, 20, 30, 40]
rev  = [500, 100, 600, 200]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [50, 80, 90, 150]
rev  = [75, 65, 25, 45]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [6, 7, 12, 13, 14]
rev  = [5, 6, 5, 3, 1]
limit = 5
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [6, 7, 12]
rev  = [5, 6, 5]
limit = 5
l = len(dist)
arr = [None]*l
print (bb(l-1))


dist = [6, 7, 8]
rev  = [5, 6, 12]
limit = 5
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [6, 9, 12, 14]
rev  = [5, 6, 3, 7]
limit = 2
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [50, 80, 90, 150]
rev  = [75, 65, 25, 45]
limit = 5
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [50, 80, 90, 150]
rev  = [75, 65, 25, 45]
limit = 30
l = len(dist)
arr = [None]*l
print (bb(l-1))

dist = [50, 80]
rev  = [75, 65]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))


dist = [50]
rev  = [75]
limit = 10
l = len(dist)
arr = [None]*l
print (bb(l-1))
