# VSR-LKH-V2
----
Reinforced Lin-Kernighan-Helsgaun Algorithms for the Traveling Salesman Problem and its Variants (VSR-LKH and VSR-LKH-3 algorithms)

VSR-LKH
----
On a Unix/Linux machine execute the following commands:

unzip VSR-LKH-V2-main.zip
cd VSR-LKH-V2-main
cd VSR-LKH-Final
make

An executable file called LKH will now be available in the directory VSR-LKH-Final.
Then execute ./run_NAME_ALPHA (./run_NAME_POPMUSIC) to calculate the instance NAME.tsp by VSR-LKH with the α-measure (POPMUSIC) method.

VSR-LKH-3
----
On a Unix/Linux machine execute the following commands:

unzip VSR-LKH-V2-main.zip
cd VSR-LKH-V2-main
cd VSR-LKH-3-Final
make

An executable file called LKH will now be available in the directory VSR-LKH-3-Final.
Then execute the following commands: 

./run_TSPTW III NAME 10000 10 0

or

./run_CTSP III NAME 10000 10 0

to calculate the instance NAME.tsptw or NAME.ctsp by VSR-LKH-3. Note that the calculated instance should be placed in the directory VSR-LKH-3-Final. The default version of VSR-LKH-3 uses the α-measure to decide the candidate sets. Set the parameter CandidateSetType = POPMUSIC in [ReadParameters.c](./VSR-LKH-3-Final/SRC/ReadParameters.c) to get the VSR-LKH-3 with the POPMUSIC method.

Data
----
All the 236 tested TSP instances from TSPLIB, National TSP, VLSI TSP benchmarks are available in [Instances](./Instances). All the 425 tested TSPTW instances and 65 tested CTSP instances are available in [VSR-LKH-3-Final/Instances](./VSR-LKH-3-Final/Instances).

Contact
----
Questions and suggestions can be sent to jzzheng@hust.edu.cn. <br> <br>
