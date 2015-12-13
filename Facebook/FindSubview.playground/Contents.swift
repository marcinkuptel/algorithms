import Foundation
import UIKit

/**
 
 You are given two identical UIView trees: A and B.
 You are also given a view from tree A. The goal is to find
 the view in tree B, which occupies the same place in
 the hierarchy as the given view from tree A.
 
 */

func findView(viewA: UIView?, viewB: UIView?, toFind: UIView) -> UIView? {
    guard let A = viewA, let B = viewB else {
        return nil
    }
    
    if A === toFind {
        return B
    }
    
    for x in 0 ..< A.subviews.count {
        if let view = findView(A.subviews[x], viewB: B.subviews[x], toFind: toFind) {
            return view
        }
    }
    
    return nil
}

//Tree A

let treeA = UIView()

let treeA_1 = UIView()
let treeA_2 = UIView()
let treeA_3 = UIView()

let treeA_3_1 = UIView()
let treeA_3_2 = UIView()

let treeA_3_1_1 = UIView()
let treeA_3_1_2 = UIView()

let treeA_3_2_1 = UIView()

treeA.addSubview(treeA_1)
treeA.addSubview(treeA_2)
treeA.addSubview(treeA_3)

treeA_3.addSubview(treeA_3_1)
treeA_3.addSubview(treeA_3_2)

treeA_3_1.addSubview(treeA_3_1_1)
treeA_3_1.addSubview(treeA_3_1_2)

treeA_3_2.addSubview(treeA_3_2_1)


//Tree B

let treeB = UIView()

let treeB_1 = UIView()
treeB_1.tag = 1
let treeB_2 = UIView()
treeB_2.tag = 2
let treeB_3 = UIView()
treeB_3.tag = 3

let treeB_3_1 = UIView()
treeB_3_1.tag = 31
let treeB_3_2 = UIView()
treeB_3_2.tag = 32

let treeB_3_1_1 = UIView()
treeB_3_1_1.tag = 311
let treeB_3_1_2 = UIView()
treeB_3_1_2.tag = 312

let treeB_3_2_1 = UIView()
treeB_3_2_1.tag = 321

treeB.addSubview(treeB_1)
treeB.addSubview(treeB_2)
treeB.addSubview(treeB_3)

treeB_3.addSubview(treeB_3_1)
treeB_3.addSubview(treeB_3_2)

treeB_3_1.addSubview(treeB_3_1_1)
treeB_3_1.addSubview(treeB_3_1_2)

treeB_3_2.addSubview(treeB_3_2_1)


//Solution

if let solution = findView(treeA, viewB: treeB, toFind: treeA_3_2_1) {
    print("Found solution: \(solution.tag)")
}else{
    print("Solution not found")
}
