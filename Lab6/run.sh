\echo "Compiling naive algorithm - seq1.cpp'"
g++ -O2 -std=c++11 -pthread -Dhome -Wall seq1.cpp -o seq1.o
echo "Compiling naive algorithm (threaded) - seq2.cpp'"
g++ -O2 -std=c++11 -pthread -Dhome -Wall seq2.cpp -o seq2.o
echo "Compiling karasuba algorithm - kar1.cpp'"
g++ -O2 -std=c++11 -pthread -Dhome -Wall kar1.cpp -o kar1.o
echo "Compiling karasuba algorithm (threaded) - kar2.cpp'"
g++ -O2 -std=c++11 -pthread -Dhome -Wall kar2.cpp -o kar2.o
echo ""

# shellcheck disable=SC2045
# shellcheck disable=SC2006
for i in `ls tests*.in`
do
  echo "Running test $i"
  head -n1 $i
#  ./seq1.o $i
#  ./seq2.o $i
#  ./kar1.o $i
  ./kar2.o $i
  echo ""
done

rm *.o

