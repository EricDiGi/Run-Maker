# Run Maker

## Project Outcomes:
Develop a C++ program that uses:
- Tab-separated file input
- Graph Algorithms
- Backtracking
- Recursion

## Preparatory Readings:
- ZyBook chapter 12: Recursion
- ZyBook chapter 18: Heaps and **Backtracking**
- ZyBook chapter 19: Graphs

## Background Information:
### Project overview:
Path planning problems appear across many business domains as well as in the everyday lives of many people.
In the case of path planning for GPS navigation for instance people usually desire the shortest path from **s** (source) to **t** (target).

Middle and long-distance runners often follow very regimented training plans that outline distances and paces to be run each day.
The process of figuring out _where_ to do a run can be a cumbersome process.
The goal of this project is to create a tool that can read in map data and find paths where **s**=**t** (loops) and the distance of the loop is as close to possible as the target distance.
An additional constraint is that a loop should be as entertaining as possible and thus should not re-use segments of the road.

Since the entire world (except the US, Myanmar, and Liberia) is on the metric system, this project will use kilometers to define distances of each road segment.

### Project Requirements:
Your application must function as described below:
1. Prompt a user for the file containing the road network data.
1. Read in road segment data from a file and create an underlying road network to enable queries.
	1. See [Sample Data](#sample-data) below for the format of the data.
		1. A header row explaining the fields will be present in the file.
		1. Fields on each line will be tab-separated and no field will contain whitespace.
1. Prompt a user for a starting location, this should be the vertex number to start at.
1. Prompt a user for the prescribed distance to run.
1. Output the route that is closest to the distance given.

#### Sample Data
The Ascii image below of a road network matches the file format data that follows it.
Road segment distances are not to scale due to limitations of such a representation.
```
       0
      / \
   A /   \ C
    /  B  \
    1-----2
    \     /
 Foo \   / Bar
      \ /
       3
```

[simple.tsv](simple.tsv)
```
endpoint-1	endpoint-2	distance-in-kilometers	road-name
0	1	1.000	A  
1	2	1.000	B  
0	2	1.000	C  
1	3	2.000	Foo
2	3	2.000	Bar
```

- To test your program on a larger data set, the file [large.tsv](large.tsv) (a subset of the San Francisco dataset here https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm) can be used.

### Implementation Notes:
1. Create a project that is object oriented, therefore there should be several classes.
2. The input file will match the exact format given above.

### Submission Requirements:
1. All code must be added and committed to your local git repository.
2. All code must be pushed to the GitHub repository created when you "accepted" the assignment.
	1. After pushing, with `git push origin main`, visit the web URL of your repository to verify that your code is there.
	If you don't see the code there, then we can't see it either.
3. Your code must compile and run. The auto-grading tests will indicate your score for your submission.
	1. The auto-grading build should begin automatically when you push your code to GitHub.
	2. If your program will not compile, the graders will not be responsible for trying to test it.
	3. You should get an email regarding the status of your build, if it does not pass, keep trying.

## Header files
The header files and [main.cpp](main.cpp) used in the instructor solution are given for this assignment.
The layout of the classes is not meant to be prescriptive.
If you would prefer to design your methods and instance variables differently, feel free.
The hpp files are meant to help and if they do not help, modify as needed (or start from scratch).

Below is a summary of the instance variables and methods that might not be completely obvious.

### Road
- `static constexpr double EPSILON = 0.001;`
	- This is a small value that can be used to check for equality since the distance of a road is a floating point number.
- `bool operator == (const Road& otherRoad) const;`
	- This equality comparison is needed in order to test that two roads are _the same_.
- `friend std::ostream& operator << (std::ostream & out, const Road & roadToShow);`
	- This method is what enables the printing out of **Road** objects. Without it, test failures and debugging efforts would not be very helpful.

### Route
- This is an object used for storing routes in the network.
It is often very helpful to create response objects rather than utilizing simple arrays of the parts, in this case **Road** objects.
- `double distance = 0.0;`
	- The sum of all **Road** distances in this **Route**.
- `std::vector<Road> legs;`
	- Vector used fore storing the parts that make up the route.
- `bool Includes (Road roadToSearchFor) const;`
	- Method for checking whether a particular **Road** has already been included in the **Route** or not.
	- Needed to ensure our **Route** doesn't loop back on itself.
- `bool operator == (const Route& otherRoute) const;`
	- Useful for checking if two routes are equal.
	- Equality should imply that the same **Road**s are included in both **Route**s being compared.
- `friend std::ostream & operator << (std::ostream & out, const Route & routeToShow);`
	- Needed to ensure output that complies to the expected output of the tests.

### FileReader
- `bool SetFile (std::string filename);`
	- Takes the name of the input file and returns true if the file is valid and can be opened.
- `~FileReader ();`
	- Destructor, used for ensuring that the input file resource is properly closed.
- `void IgnoreHeader ();`
	- The input tab-separated files have a header row. This method simply ignores that header data.
- `void LoadData (RoadGraph &g);`
	- Loads the data from the input file into the given **RoadGraph** object.

### RoadGraph
- `bool ValidVertices (int i, int j);`
	- Returns true if the given vertices are within the bounds of the input graph data.
- `Route FindLoop(int startingVertex, double distance);`
	- Used to find a loop which starts and ends at the same vertex and gets close to the prescribed distance.
- `Route FindRoute (Route routeSoFar, int startingVertex, int endingVertex, double distance);`
	- The recursive method used by `FindLoop` that explores path options and returns the _best_ one.
- `bool IsBetter (const Route & candidate, const Route & incumbant, double distance) const;`
	- Should compare the absolute value (use `fabs()`, not `abs()`) of each route when the target `distance` is subtracted.
	- Should return true if the route length of the incumbent is zero since that clearly is not the valid route.
- `bool HasOvershot (const Route & candidate, const Route & incumbant, double distance) const;`
	- Not necessary but if you've already found a route that is within 1km of the goal and the route under inspection has already overshot by more than that, there is no more need to consider this as a sub-route.
- `static constexpr double EPSILON = 0.001;`
	- Used to compare floating point numbers.
- `RoadGraph (int vertexCount = 0);`
	- Needs to allocate room for the adjacency matrix.
	- Also needs to set default value to indicate that no adjacency currently exists.
	- If you choose to implement using an adjacency list or other implementation, your allocation might differ.
- `bool AddAdjacency (int endpoint1, int endpoint2, Road r);`
	- Set the adjacency to the given **Road** objectA.
- `~RoadGraph ();`
	- Free up memory allocated by the constructor.

## Explanation
[![10 minute video explaining the project](https://res.cloudinary.com/dm3fdmzec/image/upload/v1606772096/Run_Maker_-_YouTube__ogdw30.png)](https://youtu.be/xBaHLkJoUBE)

## Important Notes:
- Projects will be graded on whether they correctly solve the problem, and whether they adhere to good programming practices.
- Projects must be received by the time specified on the due date. Projects received after that time will get a grade of zero.
- Please review the academic honesty policy.
	- Note that viewing another student's solution, whether in whole or in part, is considered academic dishonesty.
	- Also note that submitting code obtained through the Internet or other sources, whether in whole or in part, is considered academic dishonesty.
	- All programs submitted will be reviewed for evidence of academic dishonesty, and all violations will be handled accordingly.

## Grading
- View on GitHub:
	1. On your GitHub repo page, Click the :arrow_forward: **Actions** tab to see your graded results.
	1. If it isn't a green check mark (:heavy_check_mark:) then at least part of the testing failed.
	1. Click the commit message for the failing version then click "Autograding" on the left side of the page.
	1. Follow the :x: path and expand things to see what errors exist.
	1. At the bottom of the _education/autograding_ section, you can view the score for the auto-grading portion of the rubric.
		It will look something like ***40/90***.
