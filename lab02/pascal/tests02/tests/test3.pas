program test;
var
    x: integer; y: integer; z: integer;
begin
if ((x <= y and y = 3) or not (x + 3*y > 5*6 - 8)) then
begin
	writeln(y);
end else
begin
    readln(z);
end;
writeln(x);
end.
