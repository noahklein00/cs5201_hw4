-2 Just as with your SIRD model, your IG model didn't need to be templated

-3 Out of order Heun constructor arguments - you did this last time!

-2 Your IGSolver constructors have excess copy-pasting of the ODEs

-4 Your ODE solver is not iterative and cannot solve stiff ODEs

-2 No error handling/bounds check for PID controller op[]

-2 You don't need to be storing all errors for your PID controller - you only ever use the current and previous ones

-3 Your PID numerical integration is incorrect - you should be averaging the two errors to add to your "past" variable, not halving their difference.

-3 Missing preconditions for Heun template type - op+ and op* used on T

Convergence criteria for op^ is incorrect (needs to be different from Heun's), should reflect that Newton's method is for root-finding

-2 Don't use Windows line endings

-2 Don't pollute the global namespace with "using namespace std"

Your score is:
75
