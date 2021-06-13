(* GCD-Computation of x and y
   w/ Repeat-until *)
program test;
var
    x, y: integer;
begin
    writeln('Enter two numbers');
    readln(x);
    readln(y);
    repeat
        if x < y then
            y := y - x
        else if x > y then
            x := x - y;
    until x = y;
    // Output result
    writeln('GCD:');
    writeln(x);
end.