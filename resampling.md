# Resampling #

Resampling works for both up and down sampling.

"Length" of resample is the same as soure, but the density of samples is
changed.

## UpSample ##

Scale the kernel such that $1$ is the same "distance" between source samples,
then align kernel with destination sample in question.

Then find weights for each source sample in range of kernel (both horizontally
and vertically), finding the dot product of the weights with the values for the
source samples. Dividing the dot product by the sum of the weights provides the
resulting value of the sample.

Repeat this process for each pixel in the destination image. For pixels whose
kernel would be off the image, simply ignore them, and the result of the
normalizing should be sufficient to estimate the resulting sample.

Repeate for every channel of the image.

## DownSample ##

