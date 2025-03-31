#! /usr/bin/env python3

import random, sys, struct

# calcola min e max del file di 32-bit int nome
def main(nome):
  with open(nome,"rb") as f:
    b = f.read()
    num = len(b)//4
    a = struct.unpack(f"{num}i",b)
  return min(a),max(a),len(a)

if len(sys.argv)<2:
  print("Uso:\n\t %s file1 file2 ...." % sys.argv[0])
else:
  (mi,ma,nu) = main(sys.argv[1])
  for nome in sys.argv[2:]:
    (x,y,z) = main(nome)
    if(x<mi): mi = x
    if(y>ma): ma = y
    nu += z
  print(f"Min: {mi}\nMax: {ma}\nNumero interi: {nu}")

