// symbolic execution

// standard execution
// will assert be triggered?
// is there some input where that will make that assertion fail?
// is there an input that can reach that point in the program?
void foo(int x, int y){
	int y = 0;
	if(x > y){
		t = x;                // note
	}else {
		t = y;                // note
	}
	if(t < x)                 // note
	{
		assert false;
	}
}
/*
Initial:
	X	Y	T
	4	4	0

The state can be full characterized by these 3 variables,
together with knowledge of where in the program I am at.
If I start executing with X=4 Y=4 T=0

Mutation:
	X	Y	T
	4	4	4

void foo(int x(4), int y(4)){
	int y = 0;
	if(4 > 4){
		t = 4;                // note: false, go to else
	}else {
		t = 4;                // note: t assigned to 4
	}
	if(4 < 4)                 // note: no, therefore does not assert false
	{
		assert false;
	}
}
*/

/*
Initial:
	X	Y	T
	2	1	0

Test a case where the program follows a different path in the execution


Mutation:
	X	Y	T
	2	1	2

void foo(int x(2), int y(1)){
	int y = 0;
	if(2 > 1){
		t = 2;                // note: assign 2 to t, skip else
	}else {
		t = y;                // note: skipped
	}
	if(2 < 2)                 // note: no, therefore does not assert false
	{
		assert false;
	}
}
*/

/*
Analysis: On the 2 sets of inputs the program does not fail
Input Set 1:
	X	Y	T
	4	4	0
Initial Set 2:
	X	Y	T
	2	1	0
*/

/*
Symbolic Execution Goes Beyond these types of simple single input executions
Want to be able to reason about the behavior of the program on large sets of inputs
(in some cases, infinite sets of possible inputs)

Instead of concrete values of x and y, utilize a symbolic value,just a variable that allows me to give a name to this value that the user is going to provide at the input.
The state of the program is no longer a mapping from variable names to concrete values.
It is now a mapping from variable names to symbolic values.
Think of symbolic values as a formula
X=x
Y=y
T=0
*/

/*
	X	Y	T
	x	y	0

What do we know about x and y? Not much only min and max int, this means that the branching can be in either direction

void foo(int x, int y){
	int t = 0;
	if(x>y){
		t = x;                // note
	}else {
		t = y;                // note
	}
	if(t<x)                 // note
	{
		assert false;
	}
}


/*
tsub0 < x
(x >  y) => tsub0 = x
(x <= y) => tsub0 = y


tsub0 = (x >  y) => x
        (x <= y) => y
*/