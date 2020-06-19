/*!
 * \class Cost
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Cost.h"

static Cost c;

int Cost::cost_matrix[Z][Z] = { };
int Cost::GapCost = 30;
int Cost::GapGap = 30;

Cost::Cost()
{
    set_cost_pam250();
}

void Cost::set_cost_pam250()
{
    cost_matrix[C][C] = 5;
    cost_matrix[C][S] = cost_matrix[S][C] = 17;
    cost_matrix[C][T] = cost_matrix[T][C] = 19;
    cost_matrix[C][P] = cost_matrix[P][C] = 20;
    cost_matrix[C][A] = cost_matrix[A][C] = 19;
    cost_matrix[C][G] = cost_matrix[G][C] = 20;
    cost_matrix[C][N] = cost_matrix[N][C] = 21;
    cost_matrix[C][D] = cost_matrix[D][C] = 22;
    cost_matrix[C][E] = cost_matrix[E][C] = 22;
    cost_matrix[C][Q] = cost_matrix[Q][C] = 22;
    cost_matrix[C][H] = cost_matrix[H][C] = 20;
    cost_matrix[C][R] = cost_matrix[R][C] = 21;
    cost_matrix[C][K] = cost_matrix[K][C] = 22;
    cost_matrix[C][M] = cost_matrix[M][C] = 22;
    cost_matrix[C][I] = cost_matrix[I][C] = 19;
    cost_matrix[C][L] = cost_matrix[L][C] = 23;
    cost_matrix[C][V] = cost_matrix[V][C] = 19;
    cost_matrix[C][F] = cost_matrix[F][C] = 21;
    cost_matrix[C][Y] = cost_matrix[Y][C] = 17;
    cost_matrix[C][W] = cost_matrix[W][C] = 25;

    cost_matrix[S][S] = 15;
    cost_matrix[S][T] = cost_matrix[T][S] = 16;
    cost_matrix[S][P] = cost_matrix[P][S] = 16;
    cost_matrix[S][A] = cost_matrix[A][S] = 16;
    cost_matrix[S][G] = cost_matrix[G][S] = 16;
    cost_matrix[S][N] = cost_matrix[N][S] = 16;
    cost_matrix[S][D] = cost_matrix[D][S] = 17;
    cost_matrix[S][E] = cost_matrix[E][S] = 17;
    cost_matrix[S][Q] = cost_matrix[Q][S] = 18;
    cost_matrix[S][H] = cost_matrix[H][S] = 18;
    cost_matrix[S][R] = cost_matrix[R][S] = 17;
    cost_matrix[S][K] = cost_matrix[K][S] = 17;
    cost_matrix[S][M] = cost_matrix[M][S] = 19;
    cost_matrix[S][I] = cost_matrix[I][S] = 18;
    cost_matrix[S][L] = cost_matrix[L][S] = 20;
    cost_matrix[S][V] = cost_matrix[V][S] = 18;
    cost_matrix[S][F] = cost_matrix[F][S] = 20;
    cost_matrix[S][Y] = cost_matrix[Y][S] = 20;
    cost_matrix[S][W] = cost_matrix[W][S] = 19;

    cost_matrix[T][T] = 14;
    cost_matrix[T][P] = cost_matrix[P][T] = 17;
    cost_matrix[T][A] = cost_matrix[A][T] = 16;
    cost_matrix[T][G] = cost_matrix[G][T] = 17;
    cost_matrix[T][N] = cost_matrix[N][T] = 17;
    cost_matrix[T][D] = cost_matrix[D][T] = 17;
    cost_matrix[T][E] = cost_matrix[E][T] = 17;
    cost_matrix[T][Q] = cost_matrix[Q][T] = 18;
    cost_matrix[T][H] = cost_matrix[H][T] = 18;
    cost_matrix[T][R] = cost_matrix[R][T] = 18;
    cost_matrix[T][K] = cost_matrix[K][T] = 17;
    cost_matrix[T][M] = cost_matrix[M][T] = 18;
    cost_matrix[T][I] = cost_matrix[I][T] = 17;
    cost_matrix[T][L] = cost_matrix[L][T] = 19;
    cost_matrix[T][V] = cost_matrix[V][T] = 17;
    cost_matrix[T][F] = cost_matrix[F][T] = 20;
    cost_matrix[T][Y] = cost_matrix[Y][T] = 20;
    cost_matrix[T][W] = cost_matrix[W][T] = 22;

    cost_matrix[P][P] = 11;
    cost_matrix[P][A] = cost_matrix[A][P] = 16;
    cost_matrix[P][G] = cost_matrix[G][P] = 18;
    cost_matrix[P][N] = cost_matrix[N][P] = 18;
    cost_matrix[P][D] = cost_matrix[D][P] = 18;
    cost_matrix[P][E] = cost_matrix[E][P] = 18;
    cost_matrix[P][Q] = cost_matrix[Q][P] = 17;
    cost_matrix[P][H] = cost_matrix[H][P] = 17;
    cost_matrix[P][R] = cost_matrix[R][P] = 17;
    cost_matrix[P][K] = cost_matrix[K][P] = 18;
    cost_matrix[P][M] = cost_matrix[M][P] = 19;
    cost_matrix[P][I] = cost_matrix[I][P] = 19;
    cost_matrix[P][L] = cost_matrix[L][P] = 20;
    cost_matrix[P][V] = cost_matrix[V][P] = 18;
    cost_matrix[P][F] = cost_matrix[F][P] = 22;
    cost_matrix[P][Y] = cost_matrix[Y][P] = 22;
    cost_matrix[P][W] = cost_matrix[W][P] = 23;

    cost_matrix[A][A] = 15;
    cost_matrix[A][G] = cost_matrix[G][A] = 16;
    cost_matrix[A][N] = cost_matrix[N][A] = 17;
    cost_matrix[A][D] = cost_matrix[D][A] = 17;
    cost_matrix[A][E] = cost_matrix[E][A] = 17;
    cost_matrix[A][Q] = cost_matrix[Q][A] = 17;
    cost_matrix[A][H] = cost_matrix[H][A] = 18;
    cost_matrix[A][R] = cost_matrix[R][A] = 19;
    cost_matrix[A][K] = cost_matrix[K][A] = 18;
    cost_matrix[A][M] = cost_matrix[M][A] = 18;
    cost_matrix[A][I] = cost_matrix[I][A] = 18;
    cost_matrix[A][L] = cost_matrix[L][A] = 19;
    cost_matrix[A][V] = cost_matrix[V][A] = 17;
    cost_matrix[A][F] = cost_matrix[F][A] = 21;
    cost_matrix[A][Y] = cost_matrix[Y][A] = 20;
    cost_matrix[A][W] = cost_matrix[W][A] = 23;

    cost_matrix[G][G] = 12;
    cost_matrix[G][N] = cost_matrix[N][G] = 17;
    cost_matrix[G][D] = cost_matrix[D][G] = 16;
    cost_matrix[G][E] = cost_matrix[E][G] = 17;
    cost_matrix[G][Q] = cost_matrix[Q][G] = 18;
    cost_matrix[G][H] = cost_matrix[H][G] = 19;
    cost_matrix[G][R] = cost_matrix[R][G] = 20;
    cost_matrix[G][K] = cost_matrix[K][G] = 19;
    cost_matrix[G][M] = cost_matrix[M][G] = 20;
    cost_matrix[G][I] = cost_matrix[I][G] = 20;
    cost_matrix[G][L] = cost_matrix[L][G] = 21;
    cost_matrix[G][V] = cost_matrix[V][G] = 18;
    cost_matrix[G][F] = cost_matrix[F][G] = 22;
    cost_matrix[G][Y] = cost_matrix[Y][G] = 22;
    cost_matrix[G][W] = cost_matrix[W][G] = 24;

    cost_matrix[N][N] = 15;
    cost_matrix[N][D] = cost_matrix[D][N] = 15;
    cost_matrix[N][E] = cost_matrix[E][N] = 16;
    cost_matrix[N][Q] = cost_matrix[Q][N] = 16;
    cost_matrix[N][H] = cost_matrix[H][N] = 15;
    cost_matrix[N][R] = cost_matrix[R][N] = 17;
    cost_matrix[N][K] = cost_matrix[K][N] = 16;
    cost_matrix[N][M] = cost_matrix[M][N] = 19;
    cost_matrix[N][I] = cost_matrix[I][N] = 19;
    cost_matrix[N][L] = cost_matrix[L][N] = 20;
    cost_matrix[N][V] = cost_matrix[V][N] = 19;
    cost_matrix[N][F] = cost_matrix[F][N] = 21;
    cost_matrix[N][Y] = cost_matrix[Y][N] = 19;
    cost_matrix[N][W] = cost_matrix[W][N] = 21;

    cost_matrix[D][D] = 13;
    cost_matrix[D][E] = cost_matrix[E][D] = 14;
    cost_matrix[D][Q] = cost_matrix[Q][D] = 15;
    cost_matrix[D][H] = cost_matrix[H][D] = 16;
    cost_matrix[D][R] = cost_matrix[R][D] = 18;
    cost_matrix[D][K] = cost_matrix[K][D] = 17;
    cost_matrix[D][M] = cost_matrix[M][D] = 20;
    cost_matrix[D][I] = cost_matrix[I][D] = 19;
    cost_matrix[D][L] = cost_matrix[L][D] = 21;
    cost_matrix[D][V] = cost_matrix[V][D] = 19;
    cost_matrix[D][F] = cost_matrix[F][D] = 23;
    cost_matrix[D][Y] = cost_matrix[Y][D] = 21;
    cost_matrix[D][W] = cost_matrix[W][D] = 24;

    cost_matrix[E][E] = 13;
    cost_matrix[E][Q] = cost_matrix[Q][E] = 15;
    cost_matrix[E][H] = cost_matrix[H][E] = 16;
    cost_matrix[E][R] = cost_matrix[R][E] = 18;
    cost_matrix[E][K] = cost_matrix[K][E] = 17;
    cost_matrix[E][M] = cost_matrix[M][E] = 19;
    cost_matrix[E][I] = cost_matrix[I][E] = 19;
    cost_matrix[E][L] = cost_matrix[L][E] = 20;
    cost_matrix[E][V] = cost_matrix[V][E] = 19;
    cost_matrix[E][F] = cost_matrix[F][E] = 22;
    cost_matrix[E][Y] = cost_matrix[Y][E] = 21;
    cost_matrix[E][W] = cost_matrix[W][E] = 24;

    cost_matrix[Q][Q] = 13;
    cost_matrix[Q][H] = cost_matrix[H][Q] = 14;
    cost_matrix[Q][R] = cost_matrix[R][Q] = 16;
    cost_matrix[Q][K] = cost_matrix[K][Q] = 16;
    cost_matrix[Q][M] = cost_matrix[M][Q] = 18;
    cost_matrix[Q][I] = cost_matrix[I][Q] = 19;
    cost_matrix[Q][L] = cost_matrix[L][Q] = 19;
    cost_matrix[Q][V] = cost_matrix[V][Q] = 19;
    cost_matrix[Q][F] = cost_matrix[F][Q] = 22;
    cost_matrix[Q][Y] = cost_matrix[Y][Q] = 21;
    cost_matrix[Q][W] = cost_matrix[W][Q] = 22;

    cost_matrix[H][H] = 11;
    cost_matrix[H][R] = cost_matrix[R][H] = 15;
    cost_matrix[H][K] = cost_matrix[K][H] = 17;
    cost_matrix[H][M] = cost_matrix[M][H] = 19;
    cost_matrix[H][I] = cost_matrix[I][H] = 19;
    cost_matrix[H][L] = cost_matrix[L][H] = 19;
    cost_matrix[H][V] = cost_matrix[V][H] = 19;
    cost_matrix[H][F] = cost_matrix[F][H] = 19;
    cost_matrix[H][Y] = cost_matrix[Y][H] = 17;
    cost_matrix[H][W] = cost_matrix[W][H] = 20;

    cost_matrix[R][R] = 11;
    cost_matrix[R][K] = cost_matrix[K][R] = 14;
    cost_matrix[R][M] = cost_matrix[M][R] = 17;
    cost_matrix[R][I] = cost_matrix[I][R] = 19;
    cost_matrix[R][L] = cost_matrix[L][R] = 20;
    cost_matrix[R][V] = cost_matrix[V][R] = 19;
    cost_matrix[R][F] = cost_matrix[F][R] = 21;
    cost_matrix[R][Y] = cost_matrix[Y][R] = 21;
    cost_matrix[R][W] = cost_matrix[W][R] = 15;

    cost_matrix[K][K] = 12;
    cost_matrix[K][M] = cost_matrix[M][K] = 17;
    cost_matrix[K][I] = cost_matrix[I][K] = 19;
    cost_matrix[K][L] = cost_matrix[L][K] = 20;
    cost_matrix[K][V] = cost_matrix[V][K] = 19;
    cost_matrix[K][F] = cost_matrix[F][K] = 22;
    cost_matrix[K][Y] = cost_matrix[Y][K] = 21;
    cost_matrix[K][W] = cost_matrix[W][K] = 20;

    cost_matrix[M][M] = 11;
    cost_matrix[M][I] = cost_matrix[I][M] = 15;
    cost_matrix[M][L] = cost_matrix[L][M] = 13;
    cost_matrix[M][V] = cost_matrix[V][M] = 15;
    cost_matrix[M][F] = cost_matrix[F][M] = 17;
    cost_matrix[M][Y] = cost_matrix[Y][M] = 19;
    cost_matrix[M][W] = cost_matrix[W][M] = 21;

    cost_matrix[I][I] = 12;
    cost_matrix[I][L] = cost_matrix[L][I] = 15;
    cost_matrix[I][V] = cost_matrix[V][I] = 13;
    cost_matrix[I][F] = cost_matrix[F][I] = 16;
    cost_matrix[I][Y] = cost_matrix[Y][I] = 18;
    cost_matrix[I][W] = cost_matrix[W][I] = 22;

    cost_matrix[L][L] = 11;
    cost_matrix[L][V] = cost_matrix[V][L] = 15;
    cost_matrix[L][F] = cost_matrix[F][L] = 15;
    cost_matrix[L][Y] = cost_matrix[Y][L] = 18;
    cost_matrix[L][W] = cost_matrix[W][L] = 19;

    cost_matrix[V][V] = 13;
    cost_matrix[V][F] = cost_matrix[F][V] = 18;
    cost_matrix[V][Y] = cost_matrix[Y][V] = 19;
    cost_matrix[V][W] = cost_matrix[W][V] = 23;

    cost_matrix[F][F] = 8;
    cost_matrix[F][Y] = cost_matrix[Y][F] = 10;
    cost_matrix[F][W] = cost_matrix[W][F] = 17;

    cost_matrix[Y][Y] = 7;
    cost_matrix[Y][W] = cost_matrix[W][Y] = 17;

    cost_matrix[W][W] = 0;

    GapCost = 30;
    GapGap = 30;
}

void Cost::set_cost_nuc()
{
    cost_matrix[A][A] = 0;
    cost_matrix[A][C] = 1;
    cost_matrix[A][G] = 1;
    cost_matrix[A][T] = 1;
    cost_matrix[A][U] = 1;

    cost_matrix[C][A] = 1;
    cost_matrix[C][C] = 0;
    cost_matrix[C][G] = 1;
    cost_matrix[C][T] = 1;
    cost_matrix[C][U] = 1;

    cost_matrix[G][A] = 1;
    cost_matrix[G][C] = 1;
    cost_matrix[G][G] = 0;
    cost_matrix[G][T] = 1;
    cost_matrix[G][U] = 1;

    cost_matrix[T][A] = 1;
    cost_matrix[T][C] = 1;
    cost_matrix[T][G] = 1;
    cost_matrix[T][T] = 0;
    cost_matrix[T][U] = 0; //nonsense

    cost_matrix[U][A] = 1;
    cost_matrix[U][C] = 1;
    cost_matrix[U][G] = 1;
    cost_matrix[U][T] = 0; //really, nonsense
    cost_matrix[U][U] = 0;

    GapCost = 2;
    GapGap = 2;
}

//! Compare \a r and \a l and return the cost.
int Cost::cost(const char r, const char l)
{
    return cost_matrix[(int)r][(int)l];
}
