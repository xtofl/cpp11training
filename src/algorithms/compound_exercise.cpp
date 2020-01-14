
//
// task:
//
// read in a csv containing meeting schedules:
//   <room> <from (hhmm)> <duration (minutes)> <meeting name>
//   bricks, 900, 15, introduction
//   bricks, 915, 60, standard library
//   bricks, 945, 15, break
//   bricks, 1000, 60, standard library hands-on
//   cafetaria, 1200, 45, lunch
//   bricks, 1300, 15, break
//
// then, read commands from standard input:
//   sorted <column number>: print the list, sorted by column
//   overlaps: print overlapping meetings
//   holes: print space between meetings
//   room <room>: prints only meetings in <room>
//   quit
//
