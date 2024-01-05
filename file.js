var vertWallHitY = 0;
// Find the x-coordinate of the closest vertical grid intersenction
xintercept = Math.floor(player.x / TILE_SIZE) * TILE_SIZE:
xintercept += this.isRayFacingRight? TILE_SIZE: 0;
// Find the y-coordinate of the closest vertical grid intersection
yintercept = player.y + (xintercept - player.x) * Math.tan(this.rayAngle);
// Calculate the increment xstep and ystep
xstep= TILE_SIZE:
xstep = this.isRayFacingLeft ? -1 : 1;
ystep= TILE_SIZE * Math.tan(this.rayAngle);
ystep
(this.isRayFacingUp && ystep > 0) ? -1 : 1;
ystep = (this.isRayFacing Down && ystep < 0) ? −1 : 1;
*=
var nextVert TouchX = xintercept:
var nextVert Touch Y = yintercept:
if (this.isRayFacingLeft)
nextVertTouchX--;
// Increment xstep and ystep until we find a wall
while (nextVert TouchX >= 0 && nextVert TouchX <= WINDOW_WIDTH && nextVert Touch! >= 0 && nextVert Tou
if (grid.hasWallAt (nextVert TouchX, nextVert TouchY)) {
foundVertWallHit = true;
vertWallHitX = nextVert TouchX;
vertWallHitY = nextVert TouchY;
break;
}
} else {
}
nextVert TouchX += xstep;
nextVert TouchY+= ystep;
188,8
61%