# VSR-LKH-V2
----
Reinforced Lin-Kernighan-Helsgaun Algorithms for the Traveling Salesman Problem and its Variants (VSR-LKH and VSR-LKH-3 algorithms) <br> <br>

VSR-LKH
----
On a Unix/Linux machine execute the following commands: <br> <br>

unzip VSR-LKH-V2-main.zip <br>
cd VSR-LKH-V2-main <br>
cd VSR-LKH-Final <br>
make <br> <br>

An executable file called LKH will now be available in the directory VSR-LKH-Final. <br>
Then execute ./run_NAME_ALPHA (./run_NAME_POPMUSIC) to calculate the instance NAME.tsp by VSR-LKH with the α-measure (POPMUSIC) method. <br> <br>

VSR-LKH-3
----
On a Unix/Linux machine execute the following commands: <br> <br>

unzip VSR-LKH-V2-main.zip <br>
cd VSR-LKH-V2-main <br>
cd VSR-LKH-3-Final <br>
make <br> <br>

An executable file called LKH will now be available in the directory VSR-LKH-3-Final. <br>
Then execute the following commands: <br> <br>

./run_TSPTW III NAME 10000 10 0 <br> <br>

or <br> <br>

./run_CTSP III NAME 10000 10 0 <br> <br>

to calculate the instance NAME.tsptw or NAME.ctsp by VSR-LKH-3. Note that the calculated instance should be placed in the directory VSR-LKH-3-Final. The default version of VSR-LKH-3 uses the α-measure to decide the candidate sets. Set the parameter CandidateSetType = POPMUSIC in [ReadParameters.c](./VSR-LKH-3-Final/SRC/ReadParameters.c) to get the VSR-LKH-3 with the POPMUSIC method. <br> <br>

Data
----
All the 236 tested TSP instances from TSPLIB, National TSP, VLSI TSP benchmarks are available in [Instances](./Instances). All the 425 tested TSPTW instances and 65 tested CTSP instances are available in [VSR-LKH-3-Final/Instances](./VSR-LKH-3-Final/Instances). <br> <br>

Contact
----
Questions and suggestions can be sent to jzzheng@hust.edu.cn.
