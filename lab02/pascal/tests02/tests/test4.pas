program test;
var 
 no : integer;
begin
  writeln('Enter a number:');
  readln(no);

  if (no > 0) then
  begin
   writeln('You enter a Positive Number');
  end
  else begin
    if (no < 0) then
     writeln('You enter a Negative number')
    else
      if (no = 0) then
      writeln('You enter Zero');
  end;
end.