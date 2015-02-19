#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "storm.h"

int initialize_arrays (StormModel *self);

StormModel *
storm_from_default (void)
{
  StormModel *self = (StormModel*) malloc (sizeof(StormModel));

  if (self) {
    self->t = 0;
    self->dt = 1;
    self->t_end = 1;
    self->t_next = 2;
    self->shape[0] = 50;
    self->shape[1] = 25;
    self->spacing[0] = 5000.0;
    self->spacing[1] = 10000.0;
    self->center[0] = 24;
    self->center[1] = 12;
    self->sspd = 5.0;
    self->sdir = 210.0 * M_PI / 180.0;
    self->pcent = 99000.0;
    self->pedge = 101500.0;
    self->rmaxw = 65000.0;
    self->srad = 3000000.0;
    self->defcon = 0.0;
  }
  else
    return NULL;

  initialize_arrays (self);

  return self;
}


int
initialize_arrays (StormModel *self)
{
  int i;

  if (self) {
    const int n_rows = self->shape[0];
    const int n_cols = self->shape[1];

    /* Allocate memory */
    self->wdir = (double **)malloc (sizeof (double *) * n_rows);
    self->wspd = (double **)malloc (sizeof (double *) * n_rows);
    for (i = 0; i < n_rows; i++) {
      self->wdir[i] = (double *) malloc (sizeof (double) * n_cols);
      self->wspd[i] = (double *) malloc (sizeof (double) * n_cols);
    }

    if (!self->wdir || !self->wspd)
      return 1;
  }
  else
    return 1;

  return 0;
}


int
storm_free (StormModel *self)
{
  if (self) {
    free (self->wdir);
    free (self->wspd);
    free (self);
  }
  return 0;
}


int
storm_advance_time (StormModel *self)
{
  if (self) {
    storm_compute_wind (self->wdir, self->wspd,
			self->shape, self->spacing, self->center,
			self->sspd, self->sdir,
			self->pcent, self->pedge,
			self->rmaxw, self->srad, self->defcon);
    self->t += self->dt;
  }
  else
    return 1;

  return 0;
}


int
storm_compute_wind (double **wdir, double **wspd, int shape[2],
		    double spacing[2], int center[2], double sspd,
		    double sdir, double pcent, double pedge,
		    double rmaxw, double srad, double defcon)
{
  int i, j;
  const int nx = shape[0];
  const int ny = shape[1];

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      wspd[i][j] = 10.0*i + j;
    }
  }

  return 0;
}
