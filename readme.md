# DSCpp

DSCpp is a small C++ library aimed at enabling the rapid development and deployment of C++ based data-science projects. It aims to aleviate some of the frustration associated with starting a data science project in C++ while maintaining the performance gains that many C++ applications gain over the currently dominant data science platform, Python.

## Getting Started

To get started, all you need to do is clone this project to your drive and drop the files directly into your project. Note that if you adjust the file tree of any DSCpp headers, you will neeed to manually fix the #include statements embedded within them.

### Prerequisites

There are no system dependencies associated with using DSCpp in your project other than a c++17-compatible compiler. I recommend GCC, but CLANG should work as well.

If you would like to use my build system, you need to install [Meson](https://mesonbuild.com/index.html). 
    - Note that Meson requires Python3 as well as Ninja to be installed on your system. To quickly acquire Python3 as well as a functioning Pip installation on Windows, I suggest using [Anaconda](https://www.anaconda.com/distribution/#download-section). While this distribution is not strictly necessary, I find it much easier to deal with than fiddling with individual Python package isntallations. 

## Running the tests

If you would like to perform your own development or run the tests DSCpp:

- Clone the project

- Open cmd or your prefered terminal and naviagate to the directory you cloned into

- Run 'builddir'

- Navigate to the newly generated 'builddir' folder

- Run 'ninja'

- Run 't.exe'

The tests should then automatically run. 

### Testing Methodology and Styling

I aim to test as much of the code as I can. Some code-coverage tools have been employed to ensure that I hit as much as I can. Similar functions, such as constructors with only a single difference in parameter, are run inside the same test case, but within different sections. This helps make sure I don't pollute the test bench too much with redundant tests and overly-similar sections.

## Deployment

Just drop the headers into your project. Adjust the #include statements as needed.

## Built With

* [Meson](https://mesonbuild.com/index.html) - The build system used

## Versioning

We use [SemVer](http://semver.org/) for versioning.
## Authors

* **Aaron Sigal** - *Initial work* - [GitHub Account](https://github.com/AaronSigal)