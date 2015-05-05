/*!
 * \class Cost
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Cost.h"

static Cost c;

int Cost::pam250[Z][Z] = { };

Cost::Cost()
{
    pam250[C][C] = 5;
    pam250[C][S] = pam250[S][C] = 17;
    pam250[C][T] = pam250[T][C] = 19;
    pam250[C][P] = pam250[P][C] = 20;
    pam250[C][A] = pam250[A][C] = 19;
    pam250[C][G] = pam250[G][C] = 20;
    pam250[C][N] = pam250[N][C] = 21;
    pam250[C][D] = pam250[D][C] = 22;
    pam250[C][E] = pam250[E][C] = 22;
    pam250[C][Q] = pam250[Q][C] = 22;
    pam250[C][H] = pam250[H][C] = 20;
    pam250[C][R] = pam250[R][C] = 21;
    pam250[C][K] = pam250[K][C] = 22;
    pam250[C][M] = pam250[M][C] = 22;
    pam250[C][I] = pam250[I][C] = 19;
    pam250[C][L] = pam250[L][C] = 23;
    pam250[C][V] = pam250[V][C] = 19;
    pam250[C][F] = pam250[F][C] = 21;
    pam250[C][Y] = pam250[Y][C] = 17;
    pam250[C][W] = pam250[W][C] = 25;

    pam250[S][S] = 15;
    pam250[S][T] = pam250[T][S] = 16;
    pam250[S][P] = pam250[P][S] = 16;
    pam250[S][A] = pam250[A][S] = 16;
    pam250[S][G] = pam250[G][S] = 16;
    pam250[S][N] = pam250[N][S] = 16;
    pam250[S][D] = pam250[D][S] = 17;
    pam250[S][E] = pam250[E][S] = 17;
    pam250[S][Q] = pam250[Q][S] = 18;
    pam250[S][H] = pam250[H][S] = 18;
    pam250[S][R] = pam250[R][S] = 17;
    pam250[S][K] = pam250[K][S] = 17;
    pam250[S][M] = pam250[M][S] = 19;
    pam250[S][I] = pam250[I][S] = 18;
    pam250[S][L] = pam250[L][S] = 20;
    pam250[S][V] = pam250[V][S] = 18;
    pam250[S][F] = pam250[F][S] = 20;
    pam250[S][Y] = pam250[Y][S] = 20;
    pam250[S][W] = pam250[W][S] = 19;

    pam250[T][T] = 14;
    pam250[T][P] = pam250[P][T] = 17;
    pam250[T][A] = pam250[A][T] = 16;
    pam250[T][G] = pam250[G][T] = 17;
    pam250[T][N] = pam250[N][T] = 17;
    pam250[T][D] = pam250[D][T] = 17;
    pam250[T][E] = pam250[E][T] = 17;
    pam250[T][Q] = pam250[Q][T] = 18;
    pam250[T][H] = pam250[H][T] = 18;
    pam250[T][R] = pam250[R][T] = 18;
    pam250[T][K] = pam250[K][T] = 17;
    pam250[T][M] = pam250[M][T] = 18;
    pam250[T][I] = pam250[I][T] = 17;
    pam250[T][L] = pam250[L][T] = 19;
    pam250[T][V] = pam250[V][T] = 17;
    pam250[T][F] = pam250[F][T] = 20;
    pam250[T][Y] = pam250[Y][T] = 20;
    pam250[T][W] = pam250[W][T] = 22;

    pam250[P][P] = 11;
    pam250[P][A] = pam250[A][P] = 16;
    pam250[P][G] = pam250[G][P] = 18;
    pam250[P][N] = pam250[N][P] = 18;
    pam250[P][D] = pam250[D][P] = 18;
    pam250[P][E] = pam250[E][P] = 18;
    pam250[P][Q] = pam250[Q][P] = 17;
    pam250[P][H] = pam250[H][P] = 17;
    pam250[P][R] = pam250[R][P] = 17;
    pam250[P][K] = pam250[K][P] = 18;
    pam250[P][M] = pam250[M][P] = 19;
    pam250[P][I] = pam250[I][P] = 19;
    pam250[P][L] = pam250[L][P] = 20;
    pam250[P][V] = pam250[V][P] = 18;
    pam250[P][F] = pam250[F][P] = 22;
    pam250[P][Y] = pam250[Y][P] = 22;
    pam250[P][W] = pam250[W][P] = 23;

    pam250[A][A] = 15;
    pam250[A][G] = pam250[G][A] = 16;
    pam250[A][N] = pam250[N][A] = 17;
    pam250[A][D] = pam250[D][A] = 17;
    pam250[A][E] = pam250[E][A] = 17;
    pam250[A][Q] = pam250[Q][A] = 17;
    pam250[A][H] = pam250[H][A] = 18;
    pam250[A][R] = pam250[R][A] = 19;
    pam250[A][K] = pam250[K][A] = 18;
    pam250[A][M] = pam250[M][A] = 18;
    pam250[A][I] = pam250[I][A] = 18;
    pam250[A][L] = pam250[L][A] = 19;
    pam250[A][V] = pam250[V][A] = 17;
    pam250[A][F] = pam250[F][A] = 21;
    pam250[A][Y] = pam250[Y][A] = 20;
    pam250[A][W] = pam250[W][A] = 23;

    pam250[G][G] = 12;
    pam250[G][N] = pam250[N][G] = 17;
    pam250[G][D] = pam250[D][G] = 16;
    pam250[G][E] = pam250[E][G] = 17;
    pam250[G][Q] = pam250[Q][G] = 18;
    pam250[G][H] = pam250[H][G] = 19;
    pam250[G][R] = pam250[R][G] = 20;
    pam250[G][K] = pam250[K][G] = 19;
    pam250[G][M] = pam250[M][G] = 20;
    pam250[G][I] = pam250[I][G] = 20;
    pam250[G][L] = pam250[L][G] = 21;
    pam250[G][V] = pam250[V][G] = 18;
    pam250[G][F] = pam250[F][G] = 22;
    pam250[G][Y] = pam250[Y][G] = 22;
    pam250[G][W] = pam250[W][G] = 24;

    pam250[N][N] = 15;
    pam250[N][D] = pam250[D][N] = 15;
    pam250[N][E] = pam250[E][N] = 16;
    pam250[N][Q] = pam250[Q][N] = 16;
    pam250[N][H] = pam250[H][N] = 15;
    pam250[N][R] = pam250[R][N] = 17;
    pam250[N][K] = pam250[K][N] = 16;
    pam250[N][M] = pam250[M][N] = 19;
    pam250[N][I] = pam250[I][N] = 19;
    pam250[N][L] = pam250[L][N] = 20;
    pam250[N][V] = pam250[V][N] = 19;
    pam250[N][F] = pam250[F][N] = 21;
    pam250[N][Y] = pam250[Y][N] = 19;
    pam250[N][W] = pam250[W][N] = 21;

    pam250[D][D] = 13;
    pam250[D][E] = pam250[E][D] = 14;
    pam250[D][Q] = pam250[Q][D] = 15;
    pam250[D][H] = pam250[H][D] = 16;
    pam250[D][R] = pam250[R][D] = 18;
    pam250[D][K] = pam250[K][D] = 17;
    pam250[D][M] = pam250[M][D] = 20;
    pam250[D][I] = pam250[I][D] = 19;
    pam250[D][L] = pam250[L][D] = 21;
    pam250[D][V] = pam250[V][D] = 19;
    pam250[D][F] = pam250[F][D] = 23;
    pam250[D][Y] = pam250[Y][D] = 21;
    pam250[D][W] = pam250[W][D] = 24;

    pam250[E][E] = 13;
    pam250[E][Q] = pam250[Q][E] = 15;
    pam250[E][H] = pam250[H][E] = 16;
    pam250[E][R] = pam250[R][E] = 18;
    pam250[E][K] = pam250[K][E] = 17;
    pam250[E][M] = pam250[M][E] = 19;
    pam250[E][I] = pam250[I][E] = 19;
    pam250[E][L] = pam250[L][E] = 20;
    pam250[E][V] = pam250[V][E] = 19;
    pam250[E][F] = pam250[F][E] = 22;
    pam250[E][Y] = pam250[Y][E] = 21;
    pam250[E][W] = pam250[W][E] = 24;

    pam250[Q][Q] = 13;
    pam250[Q][H] = pam250[H][Q] = 14;
    pam250[Q][R] = pam250[R][Q] = 16;
    pam250[Q][K] = pam250[K][Q] = 16;
    pam250[Q][M] = pam250[M][Q] = 18;
    pam250[Q][I] = pam250[I][Q] = 19;
    pam250[Q][L] = pam250[L][Q] = 19;
    pam250[Q][V] = pam250[V][Q] = 19;
    pam250[Q][F] = pam250[F][Q] = 22;
    pam250[Q][Y] = pam250[Y][Q] = 21;
    pam250[Q][W] = pam250[W][Q] = 22;

    pam250[H][H] = 11;
    pam250[H][R] = pam250[R][H] = 15;
    pam250[H][K] = pam250[K][H] = 17;
    pam250[H][M] = pam250[M][H] = 19;
    pam250[H][I] = pam250[I][H] = 19;
    pam250[H][L] = pam250[L][H] = 19;
    pam250[H][V] = pam250[V][H] = 19;
    pam250[H][F] = pam250[F][H] = 19;
    pam250[H][Y] = pam250[Y][H] = 17;
    pam250[H][W] = pam250[W][H] = 20;

    pam250[R][R] = 11;
    pam250[R][K] = pam250[K][R] = 14;
    pam250[R][M] = pam250[M][R] = 17;
    pam250[R][I] = pam250[I][R] = 19;
    pam250[R][L] = pam250[L][R] = 20;
    pam250[R][V] = pam250[V][R] = 19;
    pam250[R][F] = pam250[F][R] = 21;
    pam250[R][Y] = pam250[Y][R] = 21;
    pam250[R][W] = pam250[W][R] = 15;

    pam250[K][K] = 12;
    pam250[K][M] = pam250[M][K] = 17;
    pam250[K][I] = pam250[I][K] = 19;
    pam250[K][L] = pam250[L][K] = 20;
    pam250[K][V] = pam250[V][K] = 19;
    pam250[K][F] = pam250[F][K] = 22;
    pam250[K][Y] = pam250[Y][K] = 21;
    pam250[K][W] = pam250[W][K] = 20;

    pam250[M][M] = 11;
    pam250[M][I] = pam250[I][M] = 15;
    pam250[M][L] = pam250[L][M] = 13;
    pam250[M][V] = pam250[V][M] = 15;
    pam250[M][F] = pam250[F][M] = 17;
    pam250[M][Y] = pam250[Y][M] = 19;
    pam250[M][W] = pam250[W][M] = 21;

    pam250[I][I] = 12;
    pam250[I][L] = pam250[L][I] = 15;
    pam250[I][V] = pam250[V][I] = 13;
    pam250[I][F] = pam250[F][I] = 16;
    pam250[I][Y] = pam250[Y][I] = 18;
    pam250[I][W] = pam250[W][I] = 22;

    pam250[L][L] = 11;
    pam250[L][V] = pam250[V][L] = 15;
    pam250[L][F] = pam250[F][L] = 15;
    pam250[L][Y] = pam250[Y][L] = 18;
    pam250[L][W] = pam250[W][L] = 19;

    pam250[V][V] = 13;
    pam250[V][F] = pam250[F][V] = 18;
    pam250[V][Y] = pam250[Y][V] = 19;
    pam250[V][W] = pam250[W][V] = 23;

    pam250[F][F] = 8;
    pam250[F][Y] = pam250[Y][F] = 10;
    pam250[F][W] = pam250[W][F] = 17;

    pam250[Y][Y] = 7;
    pam250[Y][W] = pam250[W][Y] = 17;

    pam250[W][W] = 0;
}

//! Compare \a r and \a l and return the cost.
int Cost::cost(const char r, const char l)
{
    return pam250[(int)r][(int)l];
}
