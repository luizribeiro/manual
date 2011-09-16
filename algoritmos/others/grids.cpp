/* von-Neumann */
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

for(int dr = -1; dr <= 1; dr++)
	for(int dc = -1; dc <= 1; dc++)
		if(abs(dr) + abs(dc) == 1)
			// ...


/* Moore */
int dr[] = {1, 1, 1, 0, -1, -1, -1, 0};
int dc[] = {1, 0, -1, -1, -1, 0, 1, 1};

for(int dr = -1; dr <= 1; dr++)
	for(int dc = -1; dc <= 1; dc++)
		if(abs(dr) + abs(dc) > 0)
	        //...


/* Triangular Board */
/*  --> c
   |       /\
   |      /__\
  \|/    /\  /\
        /__\/__\
   r   /\  /\  /\
      /__\/__\/__\

for cell board[i][j] adjacent ones will be [i][j-1], [i][j+1] and [i-1][j-1]
for odd j and [i+1][j+1] for even j
*/


/* Hexagonal Grid (diagonal distance, vertical distance) */
/*
              \
        __    _\| d
   |   /a \__
   |   \__/d \__
  \|/  /b \__/g \__
       \__/e \__/l \
   v   /c \__/h \__/
       \__/f \__/ 
          \__/  
         --> c
*/

int dd = { 1,1,0,-1,-1, 0};
int dv = {-1,0,1, 1, 0,-1};


/* Hexagonal Grid (row, column) */
/*
       --> c
        __    __
   |   /a \__/g \__
   |   \__/d \__/k \
  \|/  /b \__/h \__/
       \__/e \__/l \
   r   /c \__/j \__/
       \__/f \__/m \
          \__/  \__/
*/

int dr0 = { 1, -1, 0, 0, -1, -1 }; // for even columns
int dr1 = { 1, -1, 0, 0, 1, 1 }; // for odd columns
int dc = { 0, 0, 1, -1, 1, -1 };


/* 3D rectangular grid */
for(int dx = -1; dx <= 1; dx++)
	for(int dy = -1; dy <= 1; dy++)
		for(int dz = -1; dz <= 1; dz++)
			if(abs(dx) + abs(dy) + abs(dz) > 0)
				//...


/* Chess Knight */
int dr[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dc[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

for(int dr = -2; dr <= 2; dr++)
for(int dc = -2; dc <= 2; dc++)
    if(abs(dr*dc) == 2) 
        // ...
