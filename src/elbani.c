#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#define ll  long long 

ll lg2(ll x) {
	// this enables you to find lg2 in O(1)
	return 64 - __builtin_clzll(x) - 1;
}

#define max(a, b) ((a) > (b) ? (a) : (b))

/******** DEFINE VECTOR FUNCTIONALITIES ************/

//SRC: FASTER THAN SCANF readInt : https://codeforces.com/blog/entry/8080?#comment-138179
//Deleted see older commits


//THIS IS A ONE INDEXED VECTOR !!!!

typedef struct vector {
	int* vect;
	ll capacity;
	ll current;

} vector;

//Sequential O(1)
ll size_vect(vector *v) {
	return v->current - 1LL ;
}

//Sequential  O(1)
void debug_vect(vector *  v) {
	printf("### DEBUG: size=%lld, cap = %lld, curr= %lld\n" , size_vect(v), v->capacity , v->current);
}


//Sequential
struct vector * new_vector() {
	struct vector * p = malloc(sizeof(struct vector));
	// if(p == NULL) {
	// 	// fprintf(stderr, "Error: Failed malloc in new_vector call 1 \n"); fflush(stderr);     
	// 	exit(EXIT_FAILURE);
	// } 
	
	p->capacity = 1LL;
	p->current = 1LL;
	p->vect =  malloc(sizeof(*(p->vect)) * (p->capacity + 1LL));
	// if(p->vect == NULL) {
	// 	// fprintf(stderr, "Error: Failed malloc in new_vector call 2 \n"); fflush(stderr);     
	// 	exit(EXIT_FAILURE);
	// } 
	return p;
}

//PARALLEL
void copy_vect_src_to_trg(vector* src, vector* trg, ll start_src, ll start_trg, ll len) {
	//TO-DO: PARALLALIZE
	#pragma omp parallel for
	for (ll i = 0LL ; i < len ; ++i)
	{
		trg->vect[start_trg + i] = src->vect[start_src + i];
	}
}

//PARALLEL
void copy_vect_src_to_trg_rev(vector* src, vector* trg, ll start_src, ll start_trg, ll len) {
	#pragma omp parallel for
	for (ll i = 0LL ; i < len ; ++i)
	{
		trg->vect[start_trg + i] = src->vect[(start_src + len) - i - 1 ];
	}
}

//Sequential
struct vector * init_empty_vector_of_size(ll size) {
	struct vector * p = malloc(sizeof(struct vector));
	// if(p == NULL) {
	// 	// fprintf(stderr, "Error: Failed malloc in init_empty_vector_of_size call 1 \n"); fflush(stderr);     
	// 	exit(EXIT_FAILURE);
	// } 
	p->capacity = (size) ;
	p->current = (size) + 1LL;
	p->vect =  malloc(sizeof(*(p->vect)) * (p->capacity + 1LL));
	// if(p->vect == NULL) {
	// 	// fprintf(stderr, "Error: Failed malloc in init_empty_vector_of_size call 2 \n"); fflush(stderr);     
	// 	exit(EXIT_FAILURE);
	// } 
	return p ;
}

//calls a PARALLEL function
struct vector * copy_vect_at_end_and_doublesize(vector * v) {
	struct vector * p = init_empty_vector_of_size(v->capacity << 1LL);
	//this function is already parallelized
	copy_vect_src_to_trg(v, p , 1LL , v->current - 1LL, v->capacity);
	return p;
}

//calls a PARALLEL function
struct vector * copy_vect_at_end_and_doublesize_reverse(vector * v) {
	struct vector * p = init_empty_vector_of_size(v->capacity << 1LL);
	//this function is already parallelized
	copy_vect_src_to_trg_rev(v, p , 1LL , v->current - 1LL, v->capacity);
	return p;
}

//Sequential
void push(vector* v, ll data)
{
	if (v->current == v->capacity + 1LL) {
		v->capacity *= 2;
		v->vect = realloc(v->vect, (v->capacity + 1LL) * sizeof(*(v->vect)));
	}
	v->vect[v->current++] = data;
}



//Sequential O(len(v))
void print_vect(vector * v ) {
	for (ll i = 1LL ; i < v->current ; ++i) {
		printf("%d ", v->vect[i]);
	}
	printf("|\n");
}

//Sequential O(maxx)
void print_vect_from_1_to_idx(vector * v, ll maxx) {
	for (ll i = 1LL ; i <= maxx ; ++i) {
		printf("%d ", v->vect[i]);
	}
	printf("\n");
}

//Sequential
void freeVector(vector* v) {
	free(v->vect);
	free(v);
}

/******** END DEFINE VECTOR FUNCTIONALITIES ************/


/******** READ INPUT ************/
// mmap inspiration : https://gist.github.com/marcetcheverry/991042
vector* read_input_From_File(int argc, char *argv[]) {

	if (argc <= 1 ) {
		exit(-1);
	}	
	const char *filepath = argv[1];

	int fd = open(filepath, O_RDONLY, (mode_t)0600);

	if (fd == -1)
	{
		perror("Error opening file for writing");
		exit(EXIT_FAILURE);
	}
	struct stat fileInfo = {0};
	if (fstat(fd, &fileInfo) == -1)
	{
		perror("Error getting the file size");
		exit(EXIT_FAILURE);
	}
	if (fileInfo.st_size == 0)
	{
		// fprintf(stderr, "Error: File is empty, nothing to do\n");
		exit(EXIT_FAILURE);
	}

	// printf("File size is %ji\n", (intmax_t)fileInfo.st_size);

	char *map = mmap(0, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	// debug_vect(v);

	if (map == MAP_FAILED)
	{
		close(fd);
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}

	vector* v = new_vector();
	short int minus = 0;
	ll result = 0;
	for (off_t i = 0; i < fileInfo.st_size; i++)
	{
		char ch = map[i];
		// Meets a space char
		if (ch == ' ' || ch =='\n') {
			// Convert the temp char array into an integer, and add the integer into integer array
			if(i>0 && map[i-1] == ' ') continue; 
			push(v, minus ? -result : result);
			result = 0;
			minus = 0;
		}
		else if (ch == '-') {
			minus = 1;
		} else {
			result =  result * 10LL +  (ch - '0');
			if (i == fileInfo.st_size-1){
				push(v, minus ? -result : result);
			}
		}
		// printf("Found character %c at %ji\n", ch, (intmax_t)i);
	}
	// Don't forget to free the mmapped memory
	if (munmap(map, fileInfo.st_size) == -1)
	{
		close(fd);
		perror("Error un-mmapping the file");
		exit(EXIT_FAILURE);
	}
	// Un-mmaping doesn't close the file, so we still need to do that.
	close(fd);
	return v ;
}
// for (int i = 1 ; i < argc ; ++i) {
// 	printf("Reading from :  %s\n", argv[i]);
// }

/******** END READ INPUT ************/



/******** PREFIX SUM & SUFFIX SUM FUNCTIONS  ************/

//PARALLEL
void monteeSUM(vector* A ) {
	for (ll l =  lg2(A->capacity >> 1LL) - 1LL ; l >= 0LL ; --l) {
		ll maxj = ( 1LL << (l + 1LL) ) - 1LL ;
		#pragma omp parallel for
		for ( ll j =  1LL << l ; j <= maxj ; ++j) {
			A->vect[j] = A->vect[j << 1LL] + A->vect[(j << 1LL) + 1LL];
		}
	}
}

//PARALLEL
void descenteSum(vector* B, vector* A ) {

	ll maxl = lg2(B->capacity >> 1LL) ;
	//NEUTRAL ELEMENT
	B->vect[1] = 0;
	for (ll l =  1LL ; l <= maxl ; ++l ) {
		ll maxj = (1LL << (l + 1LL)) - 1LL ;

		#pragma omp parallel for
		for ( ll j =  1LL << l ; j <= maxj ; ++j) {
			if (j & 1LL) {
				//if j is odd
				B->vect[j] =  B->vect[j >> 1LL] + A->vect[j - 1LL];
			} else {
				//if j is eBen
				B->vect[j] = B->vect[j >> 1LL];
			}
		}
	}
}

//PARALLEL
vector * finaleSum(vector* A, vector *B, char reverse) {
	ll l = lg2(B->capacity >> 1LL);
	ll sizeOfResult =  B->capacity >> 1LL;
	ll maxj = (1LL << (l + 1LL)) - 1LL ;
	vector* result = init_empty_vector_of_size(sizeOfResult);
	#pragma omp parallel for
	for ( ll   j =  1LL << l ; j <= maxj ; ++j) {
		ll id = j - (1LL << l) + 1LL;
		if (!reverse) result->vect[id] = B->vect[j] +  A->vect[j];
		else     result->vect[sizeOfResult - id + 1LL] = B->vect[j] +  A->vect[j];
	}
	return result ;
}


//Uses Parallel functions
vector * getPSUM(vector * A , vector * B) {
	
	monteeSUM(A);
	descenteSum(B, A);
	return finaleSum(A, B, 0);
}

//Uses Parallel functions
vector * getSSUM(vector * A , vector * B) {
	monteeSUM(A);
	descenteSum(B, A);
	return finaleSum(A, B, 1LL);
}
/******** END PREFIX SUM & SUFFIX SUM FUNCTIONS  ************/


/******** PREFIX MAX & SUFFIX MAX FUNCTIONS  ************/

//PARALLEL
void monteeMax(vector* A ) {
	for (ll l =  lg2(A->capacity >> 1LL) - 1LL ; l >= 0LL ; --l) {
		ll maxj = ( 1LL << (l + 1LL) ) - 1LL ;
		#pragma omp parallel for
		for ( ll j =  1LL << l ; j <= maxj ; ++j) {
			A->vect[j] = max(A->vect[j << 1LL] , A->vect[(j << 1LL) + 1LL]);
		}
	}
}

//PARALLEL
void descenteMax(vector* B, vector* A ) {
	ll maxl = lg2(B->capacity >> 1LL) ;

	//NEUTRAL ELEMENT
	B->vect[1] = INT_MIN;
	for (ll l =  1LL ; l <= maxl ; ++l ) {
		ll maxj = (1LL << (l + 1LL)) - 1LL ;
		#pragma omp parallel for
		for ( ll j =  1LL << l ; j <= maxj ; ++j) {
			if (j & 1LL) {
				//if j is odd
				B->vect[j] =  max(B->vect[j >> 1LL] , A->vect[j - 1LL]);
			} else {
				//if j is even
				B->vect[j] = B->vect[j >> 1LL];
			}
		}
	}
}


//PARALLEL
vector * finaleMax(vector* A, vector *B, char rev) {
	ll l = lg2(B->capacity >> 1LL);
	ll sizeOfResult =  B->capacity >> 1LL;
	ll maxj = (1LL << (l + 1LL)) - 1LL ;
	vector* result = init_empty_vector_of_size(sizeOfResult);
	#pragma omp parallel for
	// for ( ll id = 1LL , j =  1LL << l ; j <= maxj ; ++j, ++id) {
	for ( ll   j =  1LL << l ; j <= maxj ; ++j) {
		ll id = j - (1LL << l) + 1LL;
		if (!rev) result->vect[id] = max(B->vect[j] ,  A->vect[j]);
		else     result->vect[sizeOfResult - id + 1LL] = max( B->vect[j] ,  A->vect[j]);
	}
	return result ;
}


//Uses Parallel functions
vector * getPMAX(vector * SSUM , vector * B) {
	monteeMax(SSUM);
	descenteMax(B, SSUM);
	return finaleMax(SSUM, B, 0);
}

//Uses Parallel functions
vector * getSMAX(vector * PSUM , vector * B) {
	monteeMax(PSUM);
	descenteMax(B, PSUM);
	return finaleMax(PSUM, B, 1LL);
}
/******** END PREFIX MAX & SUFFIX MAX FUNCTIONS  ************/



//Source : https://stackoverflow.com/questions/28258590/using-openmp-to-get-the-index-of-minimum-element-parallelly
typedef struct max_result {
	ll maxx;
	ll index;
} max_result;

max_result initi(){
	max_result m ;
	m.maxx = LLONG_MIN;
	m.index = LLONG_MAX;
	return m;
}

#pragma omp declare reduction(maximum : struct max_result : omp_out = (omp_in.maxx > omp_out.maxx) ? omp_in :  ((omp_in.maxx == omp_out.maxx) && (omp_in.index < omp_out.index)) ? omp_in : omp_out) initializer(omp_priv = initi())

//parallel
max_result generateM_andFindSolution(vector* v , vector* PSUM , vector* SSUM , vector* PMAX , vector* SMAX , vector* Q ) {
	ll maxsize = Q->capacity;
	struct max_result MAX;
	// MAX.maxx = PMAX->vect[1] - SSUM->vect[1] + Q->vect[1] + SMAX->vect[1] - PSUM->vect[1];
	MAX.maxx = PMAX->vect[1] - SSUM->vect[1] + Q->vect[1] + SMAX->vect[1] - PSUM->vect[1];
	MAX.index = 1;
	#pragma omp parallel for reduction(maximum:MAX)
	for (ll i = 1LL ; i <= maxsize ; ++i) {
		v->vect[i] = PMAX->vect[i] - SSUM->vect[i] + Q->vect[i] + SMAX->vect[i] - PSUM->vect[i] ;
		if (v->vect[i] > MAX.maxx) {
			MAX.maxx = v->vect[i];
			MAX.index = i;
		}
	}
	return MAX;
}

void print_Result(max_result MAX, vector* A , vector* input_vect) {
	if(MAX.maxx >=0){
		printf("%lld ", MAX.maxx);
		for ( ll i = MAX.index ; A->vect[i] == MAX.maxx && i <= input_vect-> capacity ; ++i) {
			printf("%d ", input_vect->vect[i] );
		}
	}else{
		printf("0");
	}
	
//
}


int main(int argc, char *argv[]) {
	//ADD TAG
	vector* input_vect = read_input_From_File(argc, argv);
	
    // --------------------------- IMPORTANT to economise on memory usage ---------------------------------------------- //
	//I noticed that I don't have to clean again each vector for subsequent uses...
	//for vector A the last Layer doesn't ever change
	//for vector B it always get rebuilt from scratch

	// which means I can reuse A & B for PSUM SSUM PMAX SMAX
    // --------------------------- IMPORTANT to economise on memory usage ---------------------------------------------- //

	vector* A = copy_vect_at_end_and_doublesize(input_vect);
	vector* B = init_empty_vector_of_size(A->capacity);
	vector* PSUM = getPSUM(A, B);
	
    copy_vect_src_to_trg_rev(input_vect, A , 1 , input_vect->current - 1, input_vect->capacity);
	vector* SSUM = getSSUM(A, B);

	copy_vect_src_to_trg(SSUM, A , 1 , SSUM->current - 1, SSUM->capacity);
	vector* PMAX = getPMAX(A, B);

	copy_vect_src_to_trg_rev(PSUM, A , 1 , PSUM->current - 1, PSUM->capacity);
	vector* SMAX = getSMAX(A, B);

	max_result MAX = generateM_andFindSolution(A, PSUM, SSUM, PMAX, SMAX, input_vect);
	freeVector(B);
	freeVector(PSUM);
	freeVector(SSUM);
	freeVector(PMAX);
	freeVector(SMAX);

	print_Result(MAX, A, input_vect);


	/* FREE ALLOCATED STUFF */
	freeVector(input_vect);
	freeVector(A);


	/* END FREE ALLOCATED STUFF */

	return 0;
}

