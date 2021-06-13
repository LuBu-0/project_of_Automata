program tre;
var
    i, j, n: integer; 
begin
  readln(n);
  i := n;
  repeat
    j := i;
    repeat
      writeln(':-(');
      j := j - 1;
    until j = 0;
    i := i - 1;
  until i = 0;
end.
