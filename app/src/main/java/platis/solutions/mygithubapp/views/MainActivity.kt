package platis.solutions.mygithubapp.views

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.KeyEvent
import android.view.View
import android.view.inputmethod.InputMethodManager
import android.widget.EditText
import android.widget.ProgressBar
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import platis.solutions.mygithubapp.R
import platis.solutions.mygithubapp.backend.RetrofitClient
import platis.solutions.mygithubapp.models.Repository
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class MainActivity : AppCompatActivity(), TextView.OnEditorActionListener {
    private var editTextUsername: EditText? = null
    private var progressBar: ProgressBar? = null
    private var imm: InputMethodManager? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize the variables
        editTextUsername = findViewById(R.id.editTextUserName)
        progressBar = findViewById(R.id.progressBar)
        imm = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager

        // Setting the listener to the search button
        editTextUsername?.setOnEditorActionListener(this)
    }

    override fun onEditorAction(v: TextView?, actionId: Int, event: KeyEvent?): Boolean {

        return if (v == editTextUsername) {
            // Get the text from editText

            val userName: String = editTextUsername?.text?.trim().toString()

            if (userName.isEmpty() || userName.isBlank()) {
                // Show an error to the user
                editTextUsername?.error = getString(R.string.username_cannot_be_empty)
            } else {
                // Hide the keyboard
                imm?.hideSoftInputFromWindow(editTextUsername?.windowToken, 0)

                // Show the progress bar
                progressBar?.visibility = View.VISIBLE

                // Perform the query
                getRepositoriesForUsername(userName)
            }
            true
        } else {
            false
        }
    }

    private fun getRepositoriesForUsername(userName: String) {
        RetrofitClient.instance.getRepositoriesForUsername(userName).enqueue(object : Callback<List<Repository>> {
            override fun onFailure(call: Call<List<Repository>>, t: Throwable) {
                Log.e(TAG, "Error calling GitHub: ${t.localizedMessage}")

                // Show message to user
                Toast.makeText(this@MainActivity, R.string.unable_to_get_repos, Toast.LENGTH_LONG).show()
                // Hide progress bar
                progressBar?.visibility = View.INVISIBLE
            }

            override fun onResponse(call: Call<List<Repository>>, response: Response<List<Repository>>) {
                progressBar?.visibility = View.INVISIBLE

                if (response.isSuccessful) {
                    // Get the data
                    val listOfRepos = response.body() as? ArrayList<Repository>

                    // Check if the variable is null
                    listOfRepos?.let {
                        // Create an intent
                        val intent = Intent(this@MainActivity, RepositoryActivity::class.java)
                        // Put the data to be passed
                        intent.putParcelableArrayListExtra(RepositoryActivity.KEY_REPOSITORY_DATA, it)
                        // Start the new activity
                        startActivity(intent)
                    }
                } else {
                    // Create message based on error
                    val message = when (response.code()) {
                        500 -> R.string.internal_server_error
                        401 -> R.string.unauthorized
                        403 -> R.string.forbidden
                        404 -> R.string.user_not_found
                        else -> R.string.try_another_user
                    }

                    Toast.makeText(this@MainActivity, message, Toast.LENGTH_LONG).show()
                }
            }
        })
    }

    companion object {
        private val TAG = MainActivity::class.java.simpleName
    }
}
