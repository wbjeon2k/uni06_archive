from random import randint
from random import shuffle

f = open("input.txt", "w")
ans = open("answer.txt", "w")

f.write("3\n\n")

for n in range(3):
        a = ""
            b = []

                      for i in range(255):
                                  a += str(randint(0,1))
                                      ans.write(a+'\n\n')

                                                             for i in range(144):
                                                                         p = randint(10, 200)
                                                                                 b.append(a[:p])
                                                                                                        b.append(a[p:])
                                                                                                                           shuffle(b)
                                                                                                                                         for i in b:
                                                                                                                                                     f.write(i)
                                                                                                                                                             f.write('\n')
                                                                                                                                                                              f.write('\n')
