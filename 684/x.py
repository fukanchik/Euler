L=[0,1]

def fact():
  for n in range(2,91):
    L.append(L[n-1] + L[n-2])
  return

fact()

def s(c):
  return (c%9+1)*(10**(c//9))-1

def S(k):
  ret=0
  for n in range(1, k+1):
    ret += s(n)
  return ret

print(s(2880067194370816120))
XXX=1000000007
su=0
for c in L:
  o=S(c)
  su+=o
  print(c, o%1000000, len(str(o)))
print(su % XXX)

