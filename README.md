# Parallel-Maximum-Sum-Subarray-

template for stress testing


# Project Max Sum Subarray Fait par Ilyas El Bani

Data generator for benchmarking : https://gist.github.com/ilyasELBANI/bab83efa79de77d74ef27f0caf0194b7

/******** PREFIX SUM & SUFFIX SUM FUNCTIONS  ************/

Phase 1 & 2: 
//PARALLEL
void monteeSUM(vector* A ) {

//PARALLEL
void descenteSum(vector* B, vector* A ) {

//PARALLEL
vector * finaleSum(vector* A, vector *B, char rev) {


//Uses Parallel functions
vector * getPSUM(vector * A , vector * B) {

//Uses Parallel functions
vector * getSSUM(vector * A , vector * B) {
/******** END PREFIX SUM & SUFFIX SUM FUNCTIONS  ************/

/******** PREFIX MAX & SUFFIX MAX FUNCTIONS  ************/

Phase 3 & 4: 

//PARALLEL
void monteeMax(vector* A ) {

//PARALLEL
void descenteMax(vector* B, vector* A ) {

//PARALLEL
vector * finaleMax(vector* A, vector *B, char rev) {

//Uses Parallel functions
vector * getPMAX(vector * SSUM , vector * B) {

//Uses Parallel functions
vector * getSMAX(vector * PSUM , vector * B) {

/******** END PREFIX MAX & SUFFIX MAX FUNCTIONS  ************/

/******** Generate and find Max, and indices  **********/
Phase 5 & 6 
//parallel
max_result generateM_andFindSolution(vector* v , vector* PSUM , vector* SSUM , vector* PMAX , vector* SMAX , vector* Q ) {
/******** END Generate and find Max, and indices  **********/


Utilitaires:
//Sequential O(1)
size_t size_vect(vector *v) {

//Sequential  O(1)
void debug_vect(vector *  v) {

//Sequential
struct vector * new_vector() {

//PARALLEL
void copy_vect_src_to_trg(vector* src, vector* trg, size_t start_src, size_t start_trg, size_t len) {

//PARALLEL
void copy_vect_src_to_trg_rev(vector* src, vector* trg, size_t start_src, size_t start_trg, size_t len) {

//Sequential
struct vector * init_empty_vector_of_size(size_t size) {

//calls a PARALLEL function
struct vector * copy_vect_at_end_and_doublesize(vector * v) {

//calls a PARALLEL function
struct vector * copy_vect_at_end_and_doublesize_reverse(vector * v) {

//Sequential
void push(vector* v, ll data)

//Sequential O(1)
ll get(vector* v , size_t idx)

//Sequential O(len(v))
void print_vect(vector * v ) {

//Sequential O(maxx)
void print_vect_from_1_to_idx(vector * v, size_t maxx) {

//Sequential 
void freeVector(vector* v) {
}

//Sequential
vector* read_input_From_File(int argc, char *argv[]) 

//Sequential
void print_Result(max_result MAX, vector* A , vector* input_vect) {



