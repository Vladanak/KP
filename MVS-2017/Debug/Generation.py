import sys 
import MyLibrary as My
def sum(a,b,c):
    result=(a+b)*c*b
    print (result)
    return result
    

def glavn():
    first=4
    second=25
    message="Hello World"
    k=len(message)
    s=My.Substr(message,1,2)
    rez=sum(18,first,second)
    o=My.Stepen(second,first)
    print (o)
    print (message)
    print (rez)
    print (k)
    print (s)
    return k
    

glavn()
input()