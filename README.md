# comp220-worksheetA
## Prototype

### Point Light Effect
Lighting is an important part of my project, therefore I have been working on implementing a point light into the scene to act as the campfire light that will illuminate the surrounding trees.

### Cel Shading
I have also been experimenting with Cel Shading effects on a separate branch.
![Cel Shading Teapot](ScreenShots/CelShading.png)

## Issues
I have had various issues with the prototype and so have been using RenderDoc to debug problems.
I was testing lighting and so wanted to give my tree mesh a texture just to make sure it was working but it appeared to not be working properly.
![Tree Without Texture](ScreenShots/TreeRenderdoc.png)
I used RenderDoc to try and determine what was at fault and while looking at the Mesh Output of the Tree I could see that it had no values for the vertex texture coordinates. 
![No Vertex Texture Coordinates](ScreenShots/NoTextureCoords.png)
If I want to include textures in the game I may have to find a different set of tree models that come with texture coordinates. 
I switched my Tree mesh with a Teapot mesh to make sure I was correct and the textures loaded fine. 
![Teapot Textured](ScreenShots/TeapotRenderdoc.png)
![Teapot Texture Coordinates](ScreenShots/TeapotTextureCoords.png)
