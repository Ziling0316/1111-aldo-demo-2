#include <iostream>





#define SCRN_WIDTH      320

#define SCRN_HEIGHT     200

#define ADDR_MODE		1



#define DMAC_BASE						0x10000000

#define DMAC_OFF_STATE				    0

#define DMAC_OFF_INTERRUPT              1

#define DMAC_OFF_INT_EN                 2

#define DMAC_OFF_SRCADDR                4

#define DMAC_OFF_DEST_ADDR              5

#define DMAC_OFF_DATASIZE               6

#define DMAC_OFF_OPSTART                7



/*! Fixed point arithmetic shift. */

#define SHIFT 13



/*! Fixed point co-ord shift. */

#define COORD_SHIFT 20



/*! Statically allocate memory for screen buffer. */

//char* buff_result = (char*)RESULT_BASE;

//char* buff_frame = (char*)FB_BASE;

char buff_result[SCRN_WIDTH * SCRN_HEIGHT * 3];

char buff_frame[SCRN_WIDTH * SCRN_HEIGHT * 3];



/*! Let p, s represent (px + i.py), (sx + i.sy)

*  Initially:

*    p = s         =>  (px, py) = (sx, sy)

*

*  Iterate calculation:

*    p' = p^2 + s  =>  (px', py') = (px*px - py*py + sx, 2*px*py + sy)

*

*  All performed using fixed-point arithmetic with precision 'SHIFT'.

*/



#define CONST_VALUE (256 / 2)



int brot(long sx, long sy)

{

	int count;

	long px = sx, py = sy;



	long valueCheck = 4 << SHIFT;



	for (count = 0; count < CONST_VALUE; count++) {

		long px2, py2;



		px2 = (px * px) >> (SHIFT + 1);

		py2 = (py * py) >> (SHIFT + 1);



		// Terminate when (px^2 + py^2) > 2^2.

		if (px2 + py2 > valueCheck) {

			return count;

		}



		py = ((px * py) >> (SHIFT - 1)) + sy;

		px = px2 - py2 + sx;

	}

	return -1;

}



/*! Render a view of the Mandelbrot, centred on (cx, cy)

*  with each pixel covering an area of (dx x dy); all values

*  in COORD_SHIFT fixed-point units.  Pixels are doubled up

*  horizontally, so the view covers an area of (256*dx, 512*dy).

*/

void render(int cx, int cy, int dx, int dy)

{

	int sx = cx - dx * CONST_VALUE;

	int sy = 0 * dy;

	int py = sy;

	int x, y;



	int nYStart = SCRN_HEIGHT / 2;

	for (y = nYStart - 1; y >= 0; y--) {

		int px = sx;

		for (x = 0; x < SCRN_WIDTH; x += 2) {

			int offset = (y * SCRN_WIDTH + x) * 3;

			int col;

			//unsigned short pixel;

			unsigned char pixelR, pixelG, pixelB;



			// Get iteration count.

			col = brot(px >> (COORD_SHIFT - SHIFT),

				py >> (COORD_SHIFT - SHIFT));



			// Random colour mapping:

			pixelR = (col) << 1;

			pixelG = (col * 9) << 1;

			pixelB = (col * 7) << 1;



			// Plot first pair of pixels.

			buff_result[offset] = buff_result[offset + 3] = pixelR;

			buff_result[offset + 1] = buff_result[offset + 4] = pixelG;

			buff_result[offset + 2] = buff_result[offset + 5] = pixelB;



			// Plot mirror image pixels:

			offset = ((SCRN_HEIGHT - 1 - y) * SCRN_WIDTH + x) * 3;

			buff_result[offset] = buff_result[offset + 3] = pixelR;

			buff_result[offset + 1] = buff_result[offset + 4] = pixelG;

			buff_result[offset + 2] = buff_result[offset + 5] = pixelB;

			px += dx;

		}

		py -= dy;



		if ((y % 10) == 0)

		{

			printf("Calc. - %d%%\n", (nYStart - y) * 100 / (nYStart));

		}

	}



	printf("Calc. completed.\n");

}



void copy_result()

{

	int x, y;

	for (y = 0; y < SCRN_HEIGHT; ++y) {

		for (x = 0; x < SCRN_WIDTH; x++) {

			int offset = (y * SCRN_WIDTH + x) * 3;

			buff_frame[offset] = buff_result[offset];

			buff_frame[offset + 1] = buff_result[offset + 1];

			buff_frame[offset + 2] = buff_result[offset + 2];

		}

	}

	printf("Copy. completed.\n");

}



/*! Zoom in on the mandelbrot image for several frames. */

void zoom_loop(void)

{

	long cx, cy, dx, dy;

	int count;



	// Centre the view on (-1, 0)

	cx = (-1) << COORD_SHIFT;

	cy = (0) << COORD_SHIFT;



	// Calculate dx/dy values for initial view 4 units wide and high,

	// given that screen is 256 dx units across and 512 dy units high

	dx = 4 << (COORD_SHIFT - 8);  //  = (4/256) * pow(2,COORD_SHIFT)

	dy = 4 << (COORD_SHIFT - 9);  //  = (4/512) * pow(2,COORD_SHIFT)



	for (count = 0; count < 100; count++)

	{

		render(cx, cy, dx, dy);



		copy_result();



		// Zoom in and recentre slightly.

		cx -= 2 * dx;

		dx = dx * 16 / 17;

		dy = dy * 16 / 17;

	}

}



int main(int argc, char* argv[])

{

	//if (argc); // suppress compiler warning

	//if (argv); // suppress compiler warning



	printf("Fractal Display Start!\n");

	//initLCDC();

	zoom_loop();



	//for (int i = 0; i < 1000000000; i++) {}



	// Stop measuring time and calculate the elapsed time



	return 0;

}