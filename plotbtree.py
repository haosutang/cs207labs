import subprocess
from IPython.display import Image
import os.path
def plotbtree(btree, fname, redo=False, augmented=False):
    if os.path.exists(fname+".png") and not redo:
        return Image(fname+".png")
    start="""
    digraph G {
    nodesep=0.3;
    ranksep=0.2;
    margin=0.1;
    node [shape=circle];
    edge [arrowsize=0.8];
    """
    end = "}"
    assert btree.isRoot(), "Must start at root"
    lines=""
    labeldict={}
    for t in btree.preorder():
        if not t[0].uuid in labeldict:
            labeldict[t[0].uuid]=t[0]
        if not t[1].uuid in labeldict:
            labeldict[t[1].uuid]=t[1]
        lines = lines + "\"{}\" -> \"{}\"[side={}];\n".format(t[0].uuid,t[1].uuid,t[2])
    if augmented:
        end="\n".join(["\"{}\"[label=<{}<BR/><FONT POINT-SIZE=\"10\">{},{}</FONT>>]".format(k,v.data,v.size, v.count) for (k, v) in labeldict.items()])+end
    else:
        end="\n".join(["\"{}\"[label=<{}<BR/><FONT POINT-SIZE=\"10\">count={}</FONT>>]".format(k,v.data,v.count) for (k, v) in labeldict.items()])+end
       
    start = start + lines +end
    with open(fname+".dot","w") as fd:
        fd.write(start)
    subprocess.call(['./treeplot.sh', fname])
    return Image(fname+".png")