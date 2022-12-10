
def fExpRec(base: int ,exp: int) -> int:
    # base
    if exp == 0:
        return 1
    # odd
    if exp & 1:
        return base * fExpRec(base, exp-1)
    # even
    else:
        call = fExpRec(base, exp//2)
        return call*call

print(fExpRec(2,10))
print(fExpRec(2,8))
print(fExpRec(2,7))
print(fExpRec(2,1))