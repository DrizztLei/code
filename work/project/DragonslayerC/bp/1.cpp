#define A cout << "A" << endl
#define B(X,Y) cout << (X+Y) << endl
#define X 0
#define Y 1
#define Z 2
#define Q (X+Y+Z)
#inculde<iostream>

int main(int argc, char ** argv){
        A;
	        B(12,33);
		        cout << Q << endl;
			#undef Q
			#define Q 5
			        cout << Q << endl;
				        return 0;
					        }

