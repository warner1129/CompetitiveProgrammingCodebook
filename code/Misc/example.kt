import java.util.*
import java.math.BigInteger;
import kotlin.math.*
private class Scanner {
    val lines = java.io.InputStreamReader(System.`in`).readLines()
    var curLine = 0
    var st = StringTokenizer(lines[0])
    fun next(): String {
        while(!st.hasMoreTokens())
            st = StringTokenizer(lines[++curLine])
        return st.nextToken()
    }
    fun nextInt() = next().toInt()
    fun nextLong() = next().toLong()
}
fun Long.toBigInteger() = BigInteger.valueOf(this)
fun Int.toBigInteger() = BigInteger.valueOf(toLong())
fun main() {
    val sc = Scanner()
    val buf = StringBuilder()

    val mp = Array(5) { Array(5) { -1 } }
    val dx = intArrayOf( 1, 0 )
    val dy = intArrayOf( 0, 1 )
    val v = ArrayList<Int>()

    fun dfs(x: Int, y: Int, s: Int = 0) {
        for((dx,dy) in dx zip dy) dfs(x+dx, y+dy, s)
    }
    dfs(0,0)

    val st = v.toSet().toIntArray().sorted()
    println("${st.joinToString()}\n") // st.sort()

    for(i in 1..sc.nextInt()) {
        val x = st.binarySearch(sc.nextInt())
        buf.append("$x\n")
    }

    val a = BigInteger(sc.next())
    val b = sc.nextLong().toBigInteger()
    println(a * b)
    print(buf)
}
