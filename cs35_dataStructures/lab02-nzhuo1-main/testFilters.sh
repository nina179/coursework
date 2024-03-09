#!/bin/bash
rm -rf test_output
mkdir -p test_output
for transform in noRed noGreen noBlue invert grayscale flipHorizontally flipVertically; do
    echo "Transform: $transform"
    echo "----------------------"
    for image in HorizontalGradient VerticalGradient Gerbil Rose MachuPicchu; do
        echo -n "Image: $image  Result: "
        ./picfilter test_data/$image.ppm $transform test_output/${image}__${transform}.ppm >&/dev/null
        if [ ! -e "test_output/${image}__${transform}.ppm" ]; then
            # file not created; student hasn't finished transform?
            tput setaf 3; tput bold; # yellow
            echo "no file (maybe not implemented yet?)"
            tput sgr0; # reset
        else
            diff "test_data/${image}__${transform}.ppm" "test_output/${image}__${transform}.ppm" >& /dev/null
            if [ "$?" -ne 0 ]; then
                tput setaf 5; tput bold; # purple
                echo "files are different"
                tput sgr0; # reset
            else
                tput setaf 2; tput bold; # green
                echo "files match :)"
                tput sgr0; # reset
            fi
        fi
    done
    echo ""
    echo ""
done
