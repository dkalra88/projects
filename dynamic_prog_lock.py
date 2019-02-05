def new_lk(lock, i):
  n_lk = []
  for j in range(i,len(lock)):
    n_lk.append(lock[j])
  for k in range(0,i):
    n_lk.append(lock[k])
  return n_lk

def new_st (lock, k):
  a = [i for i,val in enumerate(lock) if val==k]
  poss = [(val,l-val) for val in a]
  step = [min(elem) for elem in poss]
  temp = [poss.index(val) for val in poss]
  final = [poss[i][0] for i in temp]
  return (step,final)
    
def lk(lock, key):
  if len(key) == 0:
    result = 0
  else:
    k = str(lock+key)
    if k in hash:
      return hash[k]
    step, index = new_st(lock,key[0])
    lock_n = [new_lk(lock, i) for i in index]
    pair = list(zip(step,lock_n))
    key = key[1:]
    result = min([pair[i][0]+1 +lk(pair[i][1], key) for i, val in enumerate(pair)])
    hash[k] = result
  return result

a = "ONMDPCTB"
b = "CNB"
lock = list(a)
key = list(b)
l = len(lock)
hash = {}
print(lk(lock, key))

a = "CNBCBDFD"
b = "FDBDC"
lock = list(a)
key = list(b)
l = len(lock)
hash = {}
print(lk(lock, key))

a = "CNBCBDFD"
b = "FDBDCDFCNBDBCFNDBCFCNBND"
lock = list(a)
key = list(b)
l = len(lock)
hash = {}
print(lk(lock, key))

a = "CNBCBDFD"
b = "FDBDCDFCNBDBCFNDBCFCNBNDFDBDCDFCNBDBCFNDBCFCNBND"
lock = list(a)
key = list(b)
l = len(lock)
hash = {}
print(lk(lock, key))
