# Random array
### Time
![image](https://github.com/user-attachments/assets/1e46b4d3-05c9-4f81-aea1-40975ff3ac1c)

### Comparisons
![image](https://github.com/user-attachments/assets/53163fed-cad0-4a3e-9765-2d9e4c065646)

`Ternary String-QuickSort (TSQS)` (жёлтая) даёт самый крутой рост и по времени, и по количеству сравнений - из-за побуквенных проверок.  
`MSD-radix` (коричневая) и `MSD+QuickSort` (голубая) имеют самое низкое время и число сравнений.  

# Almost sorted array
### Time
![image](https://github.com/user-attachments/assets/50f7acfa-6621-4d01-8b43-6afedf024648)
### Comparisons
![image](https://github.com/user-attachments/assets/41fd41f0-60ae-4657-9d17-91c45495ae72)

`TSQS` (жёлтая) растёт сильнее всех - из-за множества побуквенных сравнений.  
Классический `QuickSort` (синяя) и `MergeSort` (красная) работают за O(n log n).  
`LCP-Merge` (зелёная) экономит сравнения на совпадающих префиксах и по времени между `QS` и `TSQS`.  
`MSD-radix` (коричневая) и `MSD+QS` (голубая) - самые быстрые и с минимальным числом сравнений.  

# Reverse sorted array
### Time
![image](https://github.com/user-attachments/assets/4517be93-e572-455b-9ed2-9eb7a6fcb4a8)
### Comparisons
![image](https://github.com/user-attachments/assets/265968cd-e2e4-48bb-a376-4bd5060478f3)

`TSQS` (жёлтая) остаётся самым медлительным - из-за множества побуквенных сравнений.  
`LCP-Merge` (зелёная) проигрывает обычному Merge.  
Стандартный `MergeSort` (красная) работает за O(n log n) с умеренным ростом времени.  
`QuickSort` (синяя) - тоже O(n log n), но чуть быстрее Merge.  
`MSD-radix` (коричневая) и MSD+QS (голубая) почти линейное время и минимальное число сравнений.  

# Array with common prefix
### Time
![image](https://github.com/user-attachments/assets/113d314d-3f29-4f0a-a452-16a1df7aabeb)
### Comparisons
![image](https://github.com/user-attachments/assets/b0470a2a-e072-42a0-92c3-3c48ceacdf41)

`QuickSort` и стандартный `MergeSort` выигрывают при большом n.  
`Ternary QuickSort (TSQS)` оказывается самым медленным.  
`MSD-radix и MSD+QuickSort` оказывается гораздо медленнее, чем у обычных QS/MS.  
`LCP-MergeSort` по времени работает почти так же, как обычный `Merge`.  
 
