program gcd;   
(* GCD-Computation of x and y
   w/ REPEAT UNTIL *)
var
  x, y: integer;
begin
   writeln('Please give me two numbers');
   readln(x);
   readln(y);
   repeat 
       if x < y then
            y := y - x
       else if y < x then
            x := x - y;
   until x = y;
   // Output result
   writeln('GCD:');
   writeln(x);
end.
