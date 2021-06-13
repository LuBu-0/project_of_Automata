program walk;
{ A random walk }
var
    x: integer;
    s: integer;
    b: integer;
begin
    x := 10;
    s := 0;
    repeat
        writeln(x);
        readln(b);
        b := b % 2; // randomness by user input
	    if b = 1 then 
	    begin
		    x := x + 1;
		end
		else begin
            if x <> 1 then
            begin
	             x := x - 1;
             end
             else
                x := -10;
		end;
	    s := s + 1;
    until x <= 0;
    writeln('I stopped walking after:');
    writeln(s);
    writeln('steps');
    writeln(x);
end.
