/* Q142 Mouse Clicks: by yatsen */
#include <stdio.h>
#include <string.h>
typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} region;
typedef struct {
	int x;
	int y;
} coordinate;
region regions[25];
coordinate icons[50];
int nregions;
int nicons;

int getregion(coordinate a)
{
	int r;
	for(r = nregions - 1; r >= 0; r--)
		if(regions[r].x1 <= a.x && a.x <= regions[r].x2	&& regions[r].y1 <= a.y && a.y <= regions[r].y2)
			return r;
	return -1;
}

int main()
{
	char type;
	coordinate click;
	int i, min, sqdist[50];
	while(1)
	{
		scanf("%c",&type);
		if(type == '#') break;
		if(type == 'I')
		{
			scanf("%d %d",&icons[nicons].x,&icons[nicons].y);
			nicons++;
		} else if(type == 'R')
		{
			scanf("%d %d %d %d",&regions[nregions].x1,&regions[nregions].y1,&regions[nregions].x2,&regions[nregions].y2);
			nregions++;
		} else if(type == 'M')
		{
			scanf("%d %d",&click.x,&click.y);

			i = getregion(click);
			if(i >= 0)   /* mouse click in some region */
				printf("%c\n",'A'+i);
			else /* find the closest icon */
			{
				for(i = 0; i < nicons; i++) /* caculate the distance */
					if(getregion(icons[i]) < 0) /* check if the icon in some region */
					{
						sqdist[i] = (icons[i].x - click.x) * (icons[i].x - click.x)
							+ (icons[i].y - click.y) * (icons[i].y - click.y);
					}
					else /* obscured icon need not to be considered */
						sqdist[i] = 100000000;
				min = 100000000;
				for(i = 0; i < nicons; i++) /* find the minimum value */
					if(sqdist[i] < min) min = sqdist[i];
				for(i = 0; i < nicons; i++) /* print the minimum icon(s) */
					if(sqdist[i] == min) printf("%3d",i+1);
				printf("\n");
			}
		}
	}
}
