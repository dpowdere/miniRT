#include "mlx.h"

void	*g_mlx;
void	*g_win1;
void	*g_win2;

int	gere_mouse(int x, int y, int button, void *toto)
{
	printf("Mouse event - new win\n");
	mlx_destroy_window(g_mlx, g_win1);
	win1 = mlx_new_window(g_mlx, random() % 500, random() % 500, "new win");
	mlx_mouse_hook(g_win1, gere_mouse, 0);
}

int	main(void)
{
	srandom(time(0));
	g_mlx = mlx_init();
	g_win1 = mlx_new_window(g_mlx, 300, 300, "win1");
	g_win2 = mlx_new_window(g_mlx, 600, 600, "win2");
	mlx_mouse_hook(g_win1, gere_mouse, 0);
	mlx_mouse_hook(g_win2, gere_mouse, 0);
	mlx_loop(g_mlx);
}
