(* A random walk *)
program test;
var
    x, s, b: integer;
begin
    x := 10;
    s := 0;
    repeat
        readln(b);
        b := b % 2; // randomness by user input
        if b = 1 then
            x := x + 1
        else
            x := x - 1;
        s := s + 1;
    until x <= 0;
    writeln('I stopped walking after: ');
    writeln(s);
    writeln(' steps');
end.