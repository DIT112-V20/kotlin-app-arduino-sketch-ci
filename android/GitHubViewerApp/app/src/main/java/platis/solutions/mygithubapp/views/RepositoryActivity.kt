package platis.solutions.mygithubapp.views

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import platis.solutions.mygithubapp.R
import platis.solutions.mygithubapp.adapters.RecyclerViewAdapter
import platis.solutions.mygithubapp.models.Repository

class RepositoryActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_repository)

        val listOfRepos = intent?.getParcelableArrayListExtra<Repository>(KEY_REPOSITORY_DATA)
        listOfRepos?.let {
            // Show the number of repositories
            val numberOfItems = getString(R.string.number_of_repos, it.size)
            findViewById<TextView>(R.id.textViewNumberOfRepos)?.text = numberOfItems

            // Show the list of items
            showItems(it)
        }
    }

    private fun showItems(listOfRepos: ArrayList<Repository>) {
        // Create adapter
        val recyclerViewAdapter = RecyclerViewAdapter(listOfRepos)

        // Initialize the recycler view
        val recyclerView = findViewById<RecyclerView>(R.id.recyclerView)

        // Connect adapter with recycler view
        recyclerView?.apply {
            adapter = recyclerViewAdapter
            setHasFixedSize(true)
            layoutManager = LinearLayoutManager(context)
        }
//        recyclerView?.adapter = recyclerViewAdapter
//        recyclerView?.setHasFixedSize(true)
//        recyclerView?.layoutManager = LinearLayoutManager(this)
    }

    companion object {
        const val KEY_REPOSITORY_DATA = "repositoryData"
    }
}
