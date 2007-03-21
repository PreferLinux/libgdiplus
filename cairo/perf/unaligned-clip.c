/*
 * Copyright © 2006 Jeff Muizelaar <jeff@infidigm.net>
 * Copyright © 2006 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors: Jeff Muizelaar <jeff@infidigm.net>
 *          Carl Worth <cworth@cworth.org>
 */

#include "cairo-perf.h"

static cairo_perf_ticks_t
do_unaligned_clip (cairo_t *cr, int width, int height)
{
    cairo_save (cr);

    cairo_perf_timer_start ();
    /* First a triangular clip that obviously isn't along device-pixel
     * boundaries. */
    cairo_move_to (cr, 50, 50);
    cairo_line_to (cr, 50, 90);
    cairo_line_to (cr, 90, 90);
    cairo_close_path (cr);
    cairo_clip (cr);

    /* Then a rectangular clip that would be but for the non-integer
     * scaling. */
    cairo_scale (cr, 1.1, 1.1);
    cairo_move_to (cr, 55, 55);
    cairo_line_to (cr, 90, 55);
    cairo_line_to (cr, 90, 90);
    cairo_line_to (cr, 90, 55);
    cairo_close_path (cr);

    cairo_clip (cr);
    cairo_perf_timer_stop ();

    cairo_restore (cr);

    return cairo_perf_timer_elapsed ();
}

void
unaligned_clip (cairo_perf_t *perf, cairo_t *cr, int width, int height)
{
    cairo_perf_run (perf, "unaligned_clip", do_unaligned_clip);
}