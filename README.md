# Face_Detection
The program aims to implement a face recognition parallelized algorithm using idea of Local Binary Patterns.

Two algorithms impleamented, whre one is sequential and the other is parallelized form using omp library.

DATASET:
• There are 18 different persons' pictures in our dataset with 20 pictures for each person that are
taken under different light condition and with different gestures.
• First k pictures of each person will be training images and the remaining 20-k pictures of each
person will be used as test images.
◦ Pictures are named as the following format : person_id.photo_id.txt
◦ Each file contains 2D matrices.
◦ Ex for k=10:
    ▪ training set for person 1: 1.1.txt, 1.2.txt, 1.3.txt, … , 1.10.txt
    ▪ test set for person 1: 1.11.txt, 1.12.txt, 1.13.txt, … , 1.20.txt
• All pictures in the dataset are gray scale images. Each pixel value will be an integer between 0
and 255.
• Each image is composed of 180x200 pixels.

Impleamentation: 
By running compile.sh, two executables with the names lbp_seq, and lbp_omp shall be created. 
  Runing sequential code:
    i) input following command into terminal:
            ./lbp_seq ${k} 
                          where 1<k<20,
  Runing parallel code:
    ii) input following commanf into termial:
            ./OMP_NUM_THREADS=${i} ./lbp_omp ${k}
                          where 1<k<20,
                                i = number of threads greater than 1 perferably
  
By executing run.sh profiling reports generated using gprof.
