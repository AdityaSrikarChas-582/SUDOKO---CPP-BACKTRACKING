# SUDOKO---CPP-BACKTRACKING

<p>SUDOKU ALGORITHM:<br></p>
<p>1.Find some empty space <br></p>
<p>2.Attempt to place the digits 1-9 in that space<br></p>
<p>3.Check if that digit is valid in the current spot based on the current board<br></p>
<p><list>
  <li>a. If the digit is valid, recursively attempt to fill the board using steps 1-3.<br></li>
  <li>b. If it is not valid, reset the square you just filled and go back to the previous step.<br></li>
</list></p>
<p>4.Once the board is full by the definition of this algorithm we have found a solution.<br> </p>
