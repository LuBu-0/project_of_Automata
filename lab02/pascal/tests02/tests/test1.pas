(* countdown w/ Repeat-until *)
program test;
var
    x: integer;
begin
    x := 10;
    repeat
        writeln(x);
        x := x - 1;
    until x <= 0 ;
    
end.
