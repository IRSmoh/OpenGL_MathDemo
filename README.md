I got hugely disliked the performance of GLM and wanted to roll my own library for understanding linear algebra better, this is the result.

I put only mild faith in the methods used, most of them might be right, but they may have quirks about them specifically:
If used in a 3D environment I have to invert my forward vector to move forward, while up/right work as expected. Aka I probably have Matrix4x4*Vector3f wrong.
