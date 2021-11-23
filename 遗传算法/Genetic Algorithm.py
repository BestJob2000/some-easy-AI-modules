import random
import copy
#-5 +10   pre=0.01 L=10/0.01=1000
#1000=1111101000  2^10 Lj=10
group_size=40
genLimit=150
def decode(l):
   x=0
   y=0
   for i in range(10):
      x+=l[i]*(2**(9-i))
   for i in range(10,20):
      y+=l[i]*(2**(19-i))
   x=round(-5+x/100,2)
   y=round(-5+y/100,2)
   return x,y

def eval(a,b):
   return round(float(1/(a**2+b**2+1)),6)

#Init
population=[[] for i in range(group_size)]
for i in range(group_size):
   for j in range(20):
      population[i].append(random.randint(0,1))

gennum=0
while True:
   # show
   gennum+=1
   print("\nGeneration ",gennum)
   for i in population:
      a,b=decode(i)
      print(a,b,eval(a,b))
   print()
   #Select
   all_eval=[]
   eval_sum=0
   new_population=[]
   for i in population:
      a,b=decode(i)
      all_eval.append(eval(a,b))
      eval_sum+=eval(a,b)
   for i in range(group_size):         #计算累加概率
      all_eval[i]=all_eval[i]/eval_sum
      if i>0:
         all_eval[i]=all_eval[i-1]+all_eval[i]
   for i in range(group_size):         #进行轮盘赌
      r=random.random()
      for j in range(group_size):
         if r<all_eval[j]:
            new_population.append(copy.deepcopy(population[j]))
            break
   population=copy.deepcopy(new_population)
   print("\nAfter selection")
   all_eval=[]
   for i in population:
      a,b=decode(i)
      print(a,b,eval(a,b))
      all_eval.append(eval(a,b))
   print(max(all_eval),min(all_eval))
   #交叉 交叉概率0.6
   if random.random()>0.4:
      for i in range(1,group_size,2):
         r=random.randint(0,19)
         population[i-1][r],population[i][r]=population[i][r],population[i-1][r]
      print("\nAfter intersection")
      all_eval=[]
      for i in population:
         a,b=decode(i)
         print(a,b,eval(a,b))
         all_eval.append(eval(a,b))
      print(max(all_eval),min(all_eval))
   #变异 概率0.4
   if random.random()>0.6:
      for j in range(int(group_size/10)):
         ra=random.randint(0,group_size-1)
         rb=random.randint(0,19)
         population[ra][rb]=1-population[ra][rb]
         ra=random.randint(0,group_size-1)
         rb=random.randint(0,19)
         population[ra][rb]=1-population[ra][rb]
      print("\nAfter 变异")
      all_eval=[]
      for i in population:
         a,b=decode(i)
         print(a,b,eval(a,b))
         all_eval.append(eval(a,b))
      print(max(all_eval),min(all_eval))
   #重新计算适应度 最优 最差
   if max(all_eval)>0.98 and min(all_eval)>0.95:
      break
   if gennum>genLimit:
      break
print("\nFinish")
for i in population:
         a,b=decode(i)
         if eval(a,b)==max(all_eval):
            print(a,b,eval(a,b))
            break