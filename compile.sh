echo "Syed Sarjeel Yusuf ~ 21402744"
echo "Project 3"
echo "Creating executables..."
gcc -o lbp_seq lbp_seq.c util.c util.h -lm -pg
gcc -fopenmp -o lbp_omp lbp_omp.c util.c util.h -lm -pg
echo "Executables Created!"
